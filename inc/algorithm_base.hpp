#ifndef ALGORITHM_BASE_HPP
#define ALGORITHM_BASE_HPP

#include <bitset>
#include <vector>
#include <chrono>
#include <random>
#include <limits>
#include <fstream>
#include <functional>

#include <algorithm_utility.hpp>

namespace project {

template <algorithm_value_type ValueType, std::size_t AlgorithmCount>
class algorithm_base {
public:
    static constexpr std::int64_t default_file_count = 5;
    static constexpr std::int64_t default_test_count = 21;
    static constexpr std::int64_t default_input_size = 5'000;

    algorithm_base()
        : algorithm_base(default_input_size, default_test_count) { }

    template <algorithm_container Container>
    requires std::same_as<typename Container::value_type, ValueType>
    algorithm_base(const Container& c, std::int64_t test_count = default_test_count)
        : m_vec(begin(c), end(c)),
          m_test_count{test_count},
          m_input_size{std::ssize(m_vec)}
    {
        check_argumants(m_test_count, m_input_size);
    }

    algorithm_base(std::int64_t input_size,
                   std::int64_t test_count = default_test_count)
        : m_test_count{test_count},
          m_input_size{input_size}
    {
        check_argumants(m_test_count, m_input_size);
        m_vec.reserve(m_input_size);
        generate_n(back_inserter(m_vec), m_input_size,
            [](){ return algorithm_base::generate_random_numbers(); }
        );
    }

    algorithm_base(const std::string& filename,
                   std::int64_t test_count = default_test_count)
        : m_test_count{test_count}
    {
        m_vec.reserve(default_input_size);
        std::ifstream ifs{filename};
        if (!ifs){
            throw std::runtime_error{"failed to open " + filename};
        }
        ValueType input{};
        while(ifs >> input){
            m_vec.push_back(input);
        }
        m_vec.shrink_to_fit();
        m_input_size = std::ssize(m_vec);
        check_argumants(m_test_count, m_input_size);
    }

    [[nodiscard]]
        std::int64_t get_test_count() const noexcept
    {
        return m_test_count;
    }

    [[nodiscard]]
        std::int64_t get_input_size() const noexcept
    {
        return m_input_size;
    }

    [[nodiscard]]
        std::vector<ValueType>& get_inputs() const & noexcept
    {
        return m_vec;
    }

    [[nodiscard]]
        std::vector<ValueType> get_inputs() &&
    {
        return m_vec;
    }

    template <algorithm_container Container>
    requires std::same_as<typename Container::value_type, ValueType>
    algorithm_base& operator=(const Container& c)
    {
        set(c);
        return *this;
    }

    void set_test_count(std::int64_t test_count)
    {
        m_test_count = test_count;
        check_argumants(m_test_count, m_input_size);
    }

    template <algorithm_container Container>
    requires std::same_as<typename Container::value_type, ValueType>
    void set(const Container& c, std::int64_t test_count = default_test_count)
    {
        m_test_count = test_count;
        m_vec = std::move(std::vector<ValueType>(begin(c), end(c)));
        m_input_size = std::ssize(m_vec);
        check_argumants(m_test_count, m_input_size);
    }

    void set(std::int64_t input_size,
             std::int64_t test_count = default_test_count)
    {
        check_argumants(test_count, input_size);
        m_vec.clear();
        m_vec.reserve(input_size);
        m_input_size = input_size;
        m_test_count = test_count;
        generate_n(back_inserter(m_vec), m_input_size,
            [](){ return algorithm_base::generate_random_numbers(); }
        );
    }

    void set(const std::string& filename,
             std::int64_t test_count = default_test_count)
    {
        m_vec.clear();
        m_vec.reserve(default_input_size);
        m_test_count = test_count;
        std::ifstream ifs{filename};
        if (!ifs){
            throw std::runtime_error{"failed to open " + filename};
        }
        ValueType input{};
        while(ifs >> input){
            m_vec.push_back(input);
        }
        m_vec.shrink_to_fit();
        m_input_size = std::ssize(m_vec);
        check_argumants(m_test_count, m_input_size);
    }

    static void
        generate_input_files(std::int64_t input_size = default_input_size,
                             std::int64_t file_count = default_file_count,
                             ValueType min = std::numeric_limits<ValueType>::min(),
                             ValueType max = std::numeric_limits<ValueType>::max())
    {
        for (std::int64_t i{1}; i <= file_count; ++i){
            std::ofstream ofs{"input" + std::to_string(i) + ".txt"};
            if (!ofs){
                throw std::runtime_error{
                    "failed to create input" + std::to_string(i) + ".txt"
                };
            }
            for (std::int64_t j{}; j < input_size; ++j){
                ofs << algorithm_base::generate_random_numbers(min, max) << "\n";
            }
        }
    }

    [[nodiscard]] static ValueType
        generate_random_numbers(ValueType min = std::numeric_limits<ValueType>::min(),
                                ValueType max = std::numeric_limits<ValueType>::max())
    {
        static std::mt19937_64 eng{
            static_cast<unsigned long>(
                std::chrono::system_clock::now().time_since_epoch().count()
            )
        };
        if constexpr (std::integral<ValueType>){
            static std::uniform_int_distribution<ValueType> distribution{min, max};
            return distribution(eng);
        } else if constexpr (std::floating_point<ValueType>){
            static std::uniform_real_distribution<ValueType> distribution{min, max};
            return distribution(eng);
        }
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

protected:
    std::vector<ValueType> m_vec;
    std::int64_t m_test_count{};
    std::int64_t m_input_size{};

    static constexpr int table_columns_width[]{
        13, 16, 14, 21, 21, 25, 25,
        3, 2, 3, 3
    };

    enum class format {
        left, center, right
    };

    static void check_argumants(std::int64_t test_count,
                                std::int64_t input_size)
    {
        if (input_size <= 0){
            throw std::runtime_error{
                "input size cannot be zero or negative"
            };
        }
        if (test_count <= 0){
            throw std::runtime_error{
                "test count cannot be zero or negative"
            };
        }
    }

    [[nodiscard]]
        static std::string readable(std::chrono::microseconds us)
    {
        using namespace std::chrono;
        milliseconds ms{duration_cast<milliseconds>(us % 1s)};
        seconds s{duration_cast<seconds>(us % 1min)};
        minutes min{duration_cast<minutes>(us)};
        us %= 1ms;
        std::ostringstream time;
        time << std::setw(table_columns_width[7])  << min.count() << "m "
             << std::setw(table_columns_width[8])  << s.count()   << "s "
             << std::setw(table_columns_width[9])  << ms.count()  << "ms "
             << std::setw(table_columns_width[10]) << us.count()  << "us";
        return time.str();
    }

    [[nodiscard]]
        static std::string table_column(const std::string& str,
                                        int column, const format& manip)
    {
        const auto length{std::ssize(str)};
        const auto max_length{table_columns_width[column]};
        if ((length + 2) > max_length){
            throw std::runtime_error{
                "failed to create table, table size exceeded"
            };
        }
        std::ostringstream oss;
        switch (manip){
        case format::left :
            oss << std::left << std::setw(max_length) << (" " + str);
            break;
        case format::center :
            oss << center(max_length, str);
            break;
        case format::right :
            oss << std::right << std::setw(max_length) << (str + " ");
            break;
        }
        return oss.str();
    }

    [[nodiscard]]
        static std::string table_title()
    {
        std::ostringstream oss;
        oss << table_horizontal_line('+')
            << "|" << table_column("algorithm"       , 0, format::center)
            << "|" << table_column("input size"      , 1, format::center)
            << "|" << table_column("# of tests"      , 2, format::center)
            << "|" << table_column("# of comparisons", 3, format::center)
            << "|" << table_column("# of assignments", 4, format::center)
            << "|" << table_column("median time(~)"  , 5, format::center)
            << "|" << table_column("average time(~)" , 6, format::center)
            << "|\n";
        return oss.str();
    }

    [[nodiscard]]
        static std::string table_horizontal_line(char c)
    {
        return c + std::string(table_columns_width[0], '-') + c +
                   std::string(table_columns_width[1], '-') + c +
                   std::string(table_columns_width[2], '-') + c +
                   std::string(table_columns_width[3], '-') + c +
                   std::string(table_columns_width[4], '-') + c +
                   std::string(table_columns_width[5], '-') + c +
                   std::string(table_columns_width[6], '-') + c + "\n";
    }

    using algorithmSignature =
        void(std::vector<ValueType>&, const std::int64_t&,
             std::uint64_t&, std::uint64_t&);

    template <typename Name, typename Function>
    [[nodiscard]] std::string
        compare_impl(const std::bitset<AlgorithmCount>& algorithm_select,
                     const Name (&algorithm_names)[AlgorithmCount],
                     const Function (&functions)[AlgorithmCount]) const
    {
        std::ostringstream oss;
        oss << table_title();
        for (int i{}; i < AlgorithmCount; ++i){
            if (algorithm_select[i]){
                oss << table_row(algorithm_names[i], functions[i]);
            }
        }
        oss << table_horizontal_line('+');
        return oss.str();
    }

    [[nodiscard]]
        std::string table_row(
            const std::string& name,
            const std::function<algorithmSignature>& algorithm) const
    {
        const auto& [comparison,assignment,median_time,avg_time]=perform_test(algorithm);
        std::ostringstream oss;
        oss << table_horizontal_line('|');
        oss << "|" << table_column(name                  , 0, format::center)
            << "|" << table_column(readable(m_input_size), 1, format::right )
            << "|" << table_column(readable(m_test_count), 2, format::right )
            << "|" << table_column(readable(comparison)  , 3, format::right )
            << "|" << table_column(readable(assignment)  , 4, format::right )
            << "|" << table_column(readable(median_time) , 5, format::center)
            << "|" << table_column(readable(avg_time)    , 6, format::center)
            << "|\n";
        return oss.str();
    }

    using us = std::chrono::microseconds;
    using testResults = std::tuple<std::uint64_t,std::uint64_t, us, us>;

    [[nodiscard]] testResults
        perform_test(const std::function<algorithmSignature>& algorithm) const
    {
        static std::vector<std::int64_t> time_vec;
        std::uint64_t comparison{}, assignment{};
        time_vec.reserve(m_test_count);
        for (std::int64_t i{}; i < m_test_count; ++i){
            std::vector<ValueType> temp(begin(m_vec), end(m_vec));
            auto start = std::chrono::steady_clock::now();
            std::invoke(algorithm, temp, m_input_size, comparison, assignment);
            auto end = std::chrono::steady_clock::now();
            us time_interval{std::chrono::duration_cast<us>(end - start)};
            time_vec.push_back(time_interval.count());
        }
        sort(begin(time_vec), end(time_vec));
        us median_us{time_vec[m_test_count / 2]};
        us average_us{static_cast<std::int64_t>(
            accumulate(begin(time_vec), end(time_vec), 0.)/m_test_count
        )};
        time_vec.clear();
        comparison /= m_test_count, assignment /= m_test_count;
        return std::make_tuple(comparison, assignment, median_us, average_us);
    }
};

} //namespace project

#endif // ALGORITHM_BASE_HPP
