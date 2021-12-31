#ifndef IS_CHAR_HPP
#define IS_CHAR_HPP

#include <type_traits>

namespace project {

template <typename>
struct is_char_helper
        : public std::false_type { };

template<>
struct is_char_helper<char>
        : public std::true_type { };

template<>
struct is_char_helper<wchar_t>
        : public std::true_type { };
/*
template<>
struct is_char_helper<char8_t>
        : public std::true_type { };
*/
template<>
struct is_char_helper<char16_t>
        : public std::true_type { };

template<>
struct is_char_helper<char32_t>
        : public std::true_type { };

template<>
struct is_char_helper<signed char>
        : public std::true_type { };

template<>
struct is_char_helper<unsigned char>
        : public std::true_type { };

template<typename T>
struct is_char
        : public is_char_helper<std::remove_cv_t<T>> { };

template <typename T>
inline constexpr bool is_char_v = is_char<T>::value;

} //namespace project

#endif // IS_CHAR_HPP
