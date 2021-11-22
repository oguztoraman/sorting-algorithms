#ifndef CENTER_HPP
#define CENTER_HPP

#include <iosfwd>
#include <string>
#include <iomanip>
#include <type_traits>

namespace project {

template <typename T>
struct center {
    center(int width, T str) : m_width{width}
    {
        if constexpr (std::is_same_v<T, std::string>){
            m_str = std::move(str);
        } else if constexpr(std::is_arithmetic_v<T>){
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

#endif // CENTER_HPP
