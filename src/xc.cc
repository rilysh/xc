#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <filesystem>
#include <system_error>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

#include "char_type.h"

/// @Description: Helper function to display fatal error message and then exit.
/// @Returns: fatal_error returns a void.
[[noreturn]]
static void fatal_error(const std::string_view &func)
{
    auto error = std::generic_category().default_error_condition(errno);
    std::cerr << "error: " << func << ": " << error.message() << '\n';
    std::exit(1);
}

/// @Description: Helper function to display custom fatal error message
///               and then exit.
/// @Returns: fatal_errorx returns a void.
[[noreturn]]
static void fatal_errorx(const std::string_view &emsg)
{
    std::cerr << "error: " << emsg << '\n';
    std::exit(1);
}

/// @Description: Read a file and return the unique pointer to the caller.
/// @Returns: read_file returns a std::string.
static std::string read_file(const std::string_view &fname)
{
    auto fd = open(fname.data(), O_RDONLY);
    if (fd == -1) {
        fatal_error("open()");
    }

    auto file_size = std::filesystem::file_size(fname);
    auto m_buf = std::make_unique<char[]>(file_size + 1);

    read(fd, m_buf.get(), file_size);
    return m_buf.get();
}

/// @Description: Look for a specific set of characters in the provided
///               source, and then erase them individually from the source.
/// @Returns: look_for returns a std::string.
static std::string look_for(std::string &source, std::string &matches,
			    std::int64_t times)
{
    std::int64_t times_old = times;
    std::size_t it_times = 0;

    if (times < 0) {
	fatal_errorx("size of how many, cannot be less than 0.");
    }

    for (const auto &e : matches) {
	// Times we'll find that next character from matches.
	while (times && (std::find(source.begin(), source.end(), e) != std::end(source))) {
	    source.erase(std::find(source.begin(), source.end(), e));
	    times--;
        }

	// Go to the next character from the matches iterator
	// by erasing the previous one.
        matches.erase(matches.begin(), matches.begin());
	times = times_old;
    }

    return source;
}

/// @Description: Ignore if a specific predicate matches with the provided one.
/// @Returns: ignore_if function returns a std::string.
template <typename Predicate>
static inline std::string ignore_if(const std::string &source, Predicate pred)
{
    std::string buf;
    for (const auto &item : source) {
	if (!pred(item)) {
	    buf.push_back(item);
	}
    }

    return buf;
}

/// @Description: Helper function that calls ignore_if(), clears
///               the std::string buffer, and append the returned
///               string from ignore_if() function.
/// @Returns: ignore_and_append returns a void.
template <typename Predicate>
static inline void ignore_and_append(std::string &buf, Predicate pred)
{
    const auto new_buf = ignore_if(buf, pred);
    buf.clear();
    buf.append(std::move(new_buf));
}

/// @Description: Check whether the Haystack has a specified key or not.
/// @Returns: contains_this returns a boolean value.
/// @Compat: This function mainly serves as for compatibility.
template <typename HaystackSource,
	  typename Key = std::string_view, typename =	  
	  std::enable_if_t<std::is_same_v<HaystackSource, std::string> ||
			   std::is_same_v<HaystackSource, std::string_view>>>
[[nodiscard]]
static inline bool contains_this(HaystackSource &source, const Key &key)
{
    return source.find(key) != std::string::npos;
}

/// @Description: Matches argument to check whether the argument is equal
///               to the expected one.
/// @Returns: run_args function returns a void.
static void match_args(std::string &args, std::string &buf)
{
    if (contains_this(args, "[:alnum:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::isalnum(c);
	});
    }

    if (contains_this(args, "[:alpha:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::isalpha(c);
	});
    }

    if (contains_this(args, "[:blank:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::isblank(c);
	});
    }

    if (contains_this(args, "[:cntrl:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::iscntrl(c);
	});
    }

    if (contains_this(args, "[:digit:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::isdigit(c);
	});
    }

    if (contains_this(args, "[:graph:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::isgraph(c);
	});
    }

    if (contains_this(args, "[:lower:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::islower(c);
	});
    }

    if (contains_this(args, "[:print:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::isprint(c);
	});
    }

    if (contains_this(args, "[:punct:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::ispunct(c);
	});
    }

    if (contains_this(args, "[:space:]")) {
	ignore_and_append(buf, [](int c) {
	    return char_type::isaspace(c);
	});
    }

    if (contains_this(args, "[:htab:]")) {
	ignore_and_append(buf, [](int c) {
	    return (char_type::ishtab(c));
	});
    }

    if (contains_this(args, "[:vtab:]")) {
	ignore_and_append(buf, [](int c) {
	    return (char_type::ishtab(c));
	});
    }

    if (contains_this(args, "[:newline:]")) {
	ignore_and_append(buf, [](int c) {
	    return (char_type::isnewline(c));
	});
    }

    if (contains_this(args, "[:upper:]")) {
	ignore_and_append(buf, [](int c) {
	    return (char_type::isupper(c));
	});
    }

    if (contains_this(args, "[:xdigit:]")) {
	ignore_and_append(buf, [](int c) {
	    return (char_type::isxdigit(c));
	});
    }
}

/// @Description: Print the usage of this program.
/// @Returns: print_usage() does not return anything.
[[noreturn]]
static void print_usage()
{
    std::cout << "Usage:\n"
	      << " -h    Prints this help message\n"
	      << " -f    Specify the input file\n"
	      << " -l    Specify how many non-pretyped characters to remove\n\n"
	      << "Pretypes:\n"
	      << " [:alnum:], [:alpha:], [:blank:], [:cntrl:], [:digit:]\n"
	      << " [:graph:], [:lower:], [:print:], [:punct:], [:space:]\n"
	      << " [:htab:], [:vtab:], [:newline:], [:upper:], [:xdigit:]\n";
    std::exit(1);
}

/// Entry function.
int main(int argc, char **argv)
{
    if (argc < 2) {
	fatal_errorx("argument expected.");
    }

    std::int32_t opt;
    std::string file_name;
    std::int64_t look_lim = std::numeric_limits<std::int64_t>::max();

    while ((opt = getopt(argc, argv, "hl:f:")) != -1) {
	switch (opt) {
	case 'h':
	    print_usage();
	    // Unreachable.
	    break;

	case 'l':
	    look_lim = std::atol(optarg);
	    break;

	case 'f':
	    file_name.append(optarg);
	    break;

	default:
	    std::exit(1);
	}
    }

    argc -= optind;
    argv += optind;

    if (!std::filesystem::exists(file_name)) {
	fatal_errorx("input file path was not found.");
    }

    auto file_buf = read_file(file_name.c_str());

    // Pattern (could be an arg if limit is missing after the option "-l").
    if (!argv[0]) {
        fatal_errorx("missing arguments.");
    }
    std::string arg_v1 {argv[0]};

    match_args(arg_v1, file_buf);
    if (arg_v1.find("[:") != std::string::npos) {
        arg_v1 = arg_v1.replace(arg_v1.find("[:"), arg_v1.rfind(":]") + 2, "");
    }

    look_for(file_buf, arg_v1, look_lim);
    std::cout << file_buf;
}
