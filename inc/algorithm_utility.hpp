#ifndef ALGORITHM_UTILITY_HPP
#define ALGORITHM_UTILITY_HPP

static_assert (__cplusplus >= 202002L, "c++20 required!");

#include <iomanip>
#include <concepts>

namespace project {

/* is_char_trait */

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

/* concepts for algorithm_base */

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

/* center manipulator */

template <typename T>
struct center {
    center(int width, T str) : m_width{width}
    {
        if constexpr (std::same_as<T, std::string>){
            m_str = std::move(str);
        } else if constexpr(is_arithmetic<T>){
            m_str = std::to_string(str);
        } else {
            m_str = std::string{str};
        }
    }
    int m_width;
    std::string m_str{};
};

template <typename T, typename Char, typename Traits>
inline std::basic_ostream<Char, Traits>&
    operator<<(std::basic_ostream<Char, Traits>& os, const center<T>& c)
{
    os << std::right << std::setw(c.m_width);
    os << (c.m_str + std::string((c.m_width - c.m_str.length())/2, ' '));
    return os;
}

template <typename T, typename Char, typename Traits>
inline std::basic_istream<Char, Traits>&
    operator>>(std::basic_istream<Char, Traits>& is, const center<T>& c)
{
    std::setw(c.m_width) >> std::right >> is;
    (std::string((c.m_width - c.m_str.length())/2, ' ') + c.m_str) >> is;
    return is;
}

} //namespace project

#endif // ALGORITHM_UTILITY_HPP
