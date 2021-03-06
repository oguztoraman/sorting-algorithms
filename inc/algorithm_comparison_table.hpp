/*
 * algorithm_comparison_table.hpp
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

#ifndef ALGORITHM_COMPARISON_TABLE_HPP
#define ALGORITHM_COMPARISON_TABLE_HPP

#include <tuple>
#include <chrono>
#include <iosfwd>
#include <fmt/core.h>

namespace project {
class algorithm_comparison_table {
public:
    using us_t = std::chrono::microseconds;
    using algorithm_name_t = std::string;
    using input_size_t = std::int64_t;
    using test_count_t = std::int64_t;
    using comparison_count_t = std::uint64_t;
    using assignment_count_t = std::uint64_t;
    using median_time_t = us_t;
    using avg_time_t = us_t;

    using test_results_t = std::tuple<
        algorithm_name_t,
        input_size_t,
        test_count_t,
        comparison_count_t,
        assignment_count_t,
        median_time_t,
        avg_time_t
    >;

    algorithm_comparison_table() = default;

    void add_title()
    {
        add_table_seperator_line();
        m_table += (
            column_seperator +
            column("algorithm", algorithm_name_width, format::center) +
            column_seperator +
            column("input size", input_size_width, format::center) +
            column_seperator +
            column("# of tests", test_count_width, format::center) +
            column_seperator +
            column("# of comparisons", comparison_width, format::center) +
            column_seperator +
            column("# of assignments", assignment_width, format::center) +
            column_seperator +
            column("median time(~)", median_time_width, format::center) +
            column_seperator +
            column("average time(~)", avg_time_width, format::center) +
            column_seperator + "\n"
        );
    }

    void add_table_seperator_line()
    {
        m_table += horizontal_line(table_seperator);
    }

    void add_row(const test_results_t& results)
    {
        const auto& [
            algorithm_name,
            input_size,
            test_count,
            comparison,
            assignment,
            median_time,
            avg_time
        ] = results;
        add_row_seperator_line();
        m_table += (
            column_seperator +
            column(algorithm_name, algorithm_name_width, format::center) +
            column_seperator +
            column(readable(input_size), input_size_width, format::right) +
            column_seperator +
            column(readable(test_count), test_count_width, format::right) +
            column_seperator +
            column(readable(comparison), comparison_width, format::right) +
            column_seperator +
            column(readable(assignment), assignment_width, format::right) +
            column_seperator +
            column(readable(median_time), median_time_width, format::center) +
            column_seperator +
            column(readable(avg_time), avg_time_width, format::center) +
            column_seperator + "\n"
        );
    }

    [[nodiscard]]
    static std::string readable(std::int64_t number)
    {
        auto str{std::to_string(number)};
        std::int64_t counter{};
        for (auto i{std::ssize(str)}; i >= 0; --i, ++counter){
            if (counter % 3 == 0 && counter > 0 && i != 0){
                str.insert(i, "'");
            }
        }
        return str;
    }

    [[nodiscard]]
    const std::string& get_table() const & noexcept
    {
        return m_table;
    }

    [[nodiscard]]
    std::string& get_table() & noexcept
    {
        return m_table;
    }

    [[nodiscard]]
    std::string get_table() &&
    {
        return m_table;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const algorithm_comparison_table& table)
    {
        return os << table.get_table();
    }

private:
    std::string m_table{};

    static constexpr char line_element     = '-';
    static constexpr char table_seperator  = '+';
    static constexpr char column_seperator = '|';

    static constexpr int algorithm_name_width = 13;
    static constexpr int input_size_width     = 16;
    static constexpr int test_count_width     = 14;
    static constexpr int comparison_width     = 21;
    static constexpr int assignment_width     = 21;
    static constexpr int median_time_width    = 25;
    static constexpr int avg_time_width       = 25;

    static constexpr int minutes_width      = 3;
    static constexpr int seconds_width      = 2;
    static constexpr int milliseconds_width = 3;
    static constexpr int microseconds_width = 3;

    enum class format {
        left, center, right
    };

    [[nodiscard]]
    static std::string column(const std::string& str,
           int width, const format& manip)
    {
        const auto length{std::ssize(str)};
        if ((length + 2) > width){
            throw std::runtime_error{
                "failed to create table, table size exceeded"
            };
        }
        if (manip == format::left){
            return fmt::format("{1:<{0}s}", width, (" " + str));
        }
        if (manip == format::right){
            return fmt::format("{1:>{0}s}", width, (str + " "));
        }
        return fmt::format("{1:^{0}s}", width, str);
    }

    [[nodiscard]]
    static std::string horizontal_line(char seperator)
    {
        return (
            seperator + std::string(algorithm_name_width, line_element) +
            seperator + std::string(input_size_width, line_element) +
            seperator + std::string(test_count_width, line_element) +
            seperator + std::string(comparison_width, line_element) +
            seperator + std::string(assignment_width, line_element) +
            seperator + std::string(median_time_width, line_element) +
            seperator + std::string(avg_time_width, line_element) +
            seperator + "\n"
        );
    }

    void add_row_seperator_line()
    {
        m_table += horizontal_line(column_seperator);
    }

    [[nodiscard]]
    static std::string readable(std::chrono::microseconds us)
    {
        using namespace std::chrono;
        milliseconds ms{duration_cast<milliseconds>(us % 1s)};
        seconds s{duration_cast<seconds>(us % 1min)};
        minutes min{duration_cast<minutes>(us)};
        us %= 1ms;
        return (
            fmt::format("{1:{0}}{2}", minutes_width, min.count(), "m ") +
            fmt::format("{1:{0}}{2}", seconds_width, s.count(), "s ") +
            fmt::format("{1:{0}}{2}", milliseconds_width, ms.count(), "ms ") +
            fmt::format("{1:{0}}{2}", microseconds_width, us.count(), "us")
        );
    }
};

} /* namespace project */

#endif /* ALGORITHM_COMPARISON_TABLE_HPP */
