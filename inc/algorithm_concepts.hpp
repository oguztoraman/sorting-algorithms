/*
 * algorithm_concepts.hpp
 *
 * this file is a part of sorting algorithms project.
 *
 * Copyright (C) 2022 Oğuz Toraman <oguz.toraman@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef ALGORITHM_CONCEPTS_HPP
#define ALGORITHM_CONCEPTS_HPP

static_assert (__cplusplus >= 202002L, "c++20 required!");

#include <iomanip>
#include <concepts>

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

} /* namespace project */

#endif /* ALGORITHM_CONCEPTS_HPP */
