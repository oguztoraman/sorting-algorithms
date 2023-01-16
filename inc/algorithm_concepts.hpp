//
// algorithm_concepts.hpp
// ~~~~~~~~~~~~~~~
//
//          Copyright Oğuz Toraman 2022-2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef ALGORITHM_CONCEPTS_HPP
#define ALGORITHM_CONCEPTS_HPP

static_assert (__cplusplus >= 202002L, "c++20 required!");

#include <iomanip>
#include <concepts>

namespace algorithms {

template <typename>
struct is_char_helper
        : public std::false_type { };

template<>
struct is_char_helper<char>
        : public std::true_type { };

template<>
struct is_char_helper<wchar_t>
        : public std::true_type { };

template<>
struct is_char_helper<char8_t>
        : public std::true_type { };

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
struct is_char_trait
        : public is_char_helper<std::remove_cv_t<T>> { };

template <typename T>
inline constexpr bool is_char_v = is_char_trait<T>::value;

template <typename T>
concept is_char = is_char_v<T>;

template <typename T>
concept is_arithmetic = std::integral<T> || std::floating_point<T>;

template <typename T>
concept algorithm_value_type = is_arithmetic<T> &&
        !is_char<T> && !std::same_as<T, bool>;

template <typename Container>
concept algorithm_container =
        requires (Container c){
            begin(c); end(c);
            Container::value_type;
            Container::iterator;
        } &&
        algorithm_value_type<typename Container::value_type> &&
        std::input_iterator<typename Container::iterator>;

} /* namespace algorithms */

#endif /* ALGORITHM_CONCEPTS_HPP */
