// Inline-able ctypes for C++

#ifndef CHAR_TYPE_H
# define CHAR_TYPE_H

#include <type_traits>

/// @description: Alias to std::enable_if<>::type, to type check
///               whether __IntT is an int or char at compile time.
/// @note: std::enable_if_t (for type) requires >= C++17.
template <typename __CType>
using __Type_IntOrChar = std::enable_if_t<
    std::is_same_v<std::remove_const_t<__CType>, int> ||
    std::is_same_v<std::remove_const_t<__CType>, char>>;

namespace char_type {

/// @description: Test for alphanumeric character.
/// @returns: [isalnum -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isalnum(__CType c) noexcept
{
    return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ||
	    (c >= '0' && c <= '9'));
}

/// @description: Test for alphabetic character.
/// @returns: [isalpha -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isalpha(__CType c) noexcept
{	
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/// @description: Test for control character.
/// @returns: [iscntrl -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int iscntrl(__CType c) noexcept
{
    return ((c >= '\0' && c < ' ') || c == 127);
}

/// @description: Test for numeric digit character.
/// @returns: [isdigit -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isdigit(__CType c) noexcept
{
    return (c >= '0' && c <= '9');
}

/// @description: Test for printable character, excluding space.
/// @returns: [isgraph -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isgraph(__CType c) noexcept
{
    return (c >= '!' && c <= '~');
}

/// @description: Test for lowecase character.
/// @returns: [islower -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int islower(__CType c) noexcept
{
    return (c >= 'a' && c <= 'z');
}

/// @description: Test for printable character.
/// @returns: [isprint -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isprint(__CType c) noexcept
{
    return (c >= ' ' && c <= '_');
}

/// @description: Test for punctuation character.
/// @returns: [ispunct -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int ispunct(__CType c) noexcept
{
    return (isgraph(c) && !isalnum(c));
}

/// @description: Test for space character.
/// @returns: [isspace -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isspace(__CType c) noexcept
{
    return ((c >= '\t' && c <= '\r') || c == ' ');
}

/// @description: Test for uppercase character.
/// @returns: [isupper -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isupper(__CType c) noexcept
{
    return (c >= 'A' && c <= 'Z');
}

/// @description: Test for digits and hexadecimal character.
/// @returns: [isxdigit -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isxdigit(__CType c) noexcept
{
    return (isdigit(c) || ((c >= 'a' && c <= 'f') ||
			   (c >= 'A' && c <= 'F')));
}

/// @description: Test for ASCII character.
/// @returns: [isascii -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isascii(__CType c) noexcept
{
    return ((c & ~127) == 0);
}

/// @description: Test for blank character.
/// @returns: [isblank -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isblank(__CType c) noexcept
{
    return (c == ' ' || c == '\t');
}

/// @description: Convert to lowercase character.
/// @returns: [tolower -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int tolower(__CType c) noexcept
{
    return (isupper(c) ? (c + '0' - 16) : c);
}

/// @description: Convert to uppercase character.
/// @returns: [toupper -> int]
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int toupper(__CType c) noexcept
{
    return (islower(c) ? (c - '0' + 16) : c);
}

/// @description: Test for verticle tab character.
/// @returns [isvtab -> int]
/// @note: isvtab function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isvtab(__CType c) noexcept
{
    return (c == '\v');
}

/// @description: Test for horizontal tab character.
/// @returns [ishtab -> int]
/// @note: ishtab function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int ishtab(__CType c) noexcept
{
    return (c == '\t');
}

/// @description: Test for verticle and horizontal tab character.
/// @returns [istab -> int]
/// @note: istab function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int istab(__CType c) noexcept
{
    return (isvtab(c) || ishtab(c));
}

/// @description: Test for a space character.
/// @returns [isaspace -> int]
/// @note: isaspace function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isaspace(__CType c) noexcept
{
    return (c == ' ');
}

/// @description: Test for a BEL character.
/// @returns [isbel -> int]
/// @note: isbel function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isbel(__CType c) noexcept
{
    return (c == '\a');
}

/// @description: Test for a backspace character.
/// @returns [isbackspace -> int]
/// @note: isbackspace function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isbackspace(__CType c) noexcept
{
    return (c == '\b');
}

/// @description: Test for a form-feed character.
/// @returns [isformfeed -> int]
/// @note: isformfeed function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isformfeed(__CType c) noexcept
{
    return (c == '\f');
}

/// @description: Test for a newline character.
/// @returns [isnewline -> int]
/// @note: isnewline function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isnewline(__CType c) noexcept
{
    return (c == '\n');
}

/// @description: Test for a return character.
/// @returns [isreturn -> int]
/// @note: isreturn function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isreturn(__CType c) noexcept
{
    return (c == '\r');
}

/// @description: Test for a hexadecimal lowercase character.
/// @returns [isxlower -> int]
/// @note: isxlower function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isxlower(__CType c) noexcept
{
    return (islower(c) || (c >= 'a' && c <= 'f'));
}

/// @description: Test for a hexadecimal uppercase character.
/// @returns [isxupper -> int]
/// @note: isxupper function is not POSIX standard.
template <typename __CType, typename = __Type_IntOrChar<__CType>>
constexpr inline int isxupper(__CType c) noexcept
{
    return (isupper(c) || (c >= 'A' && c <= 'F'));
}

} // namespace

#endif
