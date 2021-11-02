#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <vector>
#include <string>
#include <chrono>
#include <bitset>
#include <random>
#include <limits>
#include <fstream>
#include <numeric>
#include <cstdint>
#include <sstream>
#include <algorithm>
#include <functional>
#include <type_traits>

#include <center.hpp>
#include <is_char.hpp>

namespace project {

template <typename NumType = int>
class sorting_algorithms {
public:

    static constexpr int total_algorithm_number = 6;

    enum algorithms {
        selection = 1L << 0,
        bubble 	  = 1L << 1,
        quick     = 1L << 2,
        merge     = 1L << 3,
        insertion = 1L << 4,
        heap      = 1L << 5,

        all       = (1L << total_algorithm_number) - 1
    };

    static constexpr std::int64_t default_file_number = 5;
    static constexpr std::int64_t default_test_number = 21;
    static constexpr std::int64_t default_input_size  = 5'000;

    static_assert(
        std::is_arithmetic_v<NumType> &&
        !is_char_v<NumType> && !std::is_same_v<NumType, bool>,
        "template argument must be an integral or a floating point type"
    );

    template <typename InIter>
    sorting_algorithms(InIter beg, InIter end,
                       std::int64_t test_number = default_test_number)
        : m_vec{beg, end},
          m_test_number{test_number},
          m_input_size{std::ssize(m_vec)}
    {
        check_argumants(m_test_number, m_input_size);
    }

    sorting_algorithms(std::int64_t input_size = default_input_size,
                       std::int64_t test_number = default_test_number)
        : m_test_number{test_number},
          m_input_size{input_size}
    {
        check_argumants(m_test_number, m_input_size);
        m_vec.reserve(m_input_size);
        for (std::int64_t i{}; i < m_input_size; ++i){
            m_vec.push_back(
                sorting_algorithms::generate_random_numbers()
            );
        }
    }

    sorting_algorithms(const std::string& filename,
                       std::int64_t test_number = default_test_number)
        : m_test_number{test_number}
    {
        m_vec.reserve(default_input_size);
        std::ifstream ifs{filename};
        if (!ifs){
            throw std::runtime_error{"failed to open " + filename};
        }
        NumType input{};
        while(ifs >> input){
            m_vec.push_back(input);
        }
        m_vec.shrink_to_fit();
        m_input_size = std::ssize(m_vec);
        check_argumants(m_test_number, m_input_size);
    }

    template <typename InIter>
    void set(InIter beg, InIter end,
             std::int64_t test_number = default_test_number)
    {
        m_test_number = test_number;
        m_vec = std::move(std::vector<NumType>{beg, end});
        m_input_size = std::ssize(m_vec);
        check_argumants(m_test_number, m_input_size);
    }

    void set(std::int64_t input_size = default_input_size,
             std::int64_t test_number = default_test_number)
    {
        check_argumants(test_number, input_size);
        m_vec.clear();
        m_vec.reserve(input_size);
        m_input_size = input_size;
        m_test_number = test_number;
        for (std::int64_t i{}; i < m_input_size; ++i){
            m_vec.push_back(
                sorting_algorithms::generate_random_numbers()
            );
        }
    }

    void set(const std::string& filename,
             std::int64_t test_number = default_test_number)
    {
        m_vec.clear();
        m_vec.reserve(default_input_size);
        m_test_number = test_number;
        std::ifstream ifs{filename};
        if (!ifs){
            throw std::runtime_error{"failed to open " + filename};
        }
        NumType input{};
        while(ifs >> input){
            m_vec.push_back(input);
        }
        m_vec.shrink_to_fit();
        m_input_size = std::ssize(m_vec);
        check_argumants(m_test_number, m_input_size);
    }

    static void
        generate_input_files(std::int64_t input_size = default_input_size,
                             std::int64_t file_number = default_file_number,
                             NumType min = std::numeric_limits<NumType>::min(),
                             NumType max = std::numeric_limits<NumType>::max())
    {
        for (std::int64_t i{1}; i <= file_number; ++i){
            std::ofstream ofs{"input" + std::to_string(i) + ".txt"};
            if (!ofs){
                throw std::runtime_error{
                    "failed to create input" + std::to_string(i) + ".txt"
                };
            }
            for (std::int64_t j{}; j < input_size; ++j){
                ofs << sorting_algorithms::generate_random_numbers(min, max) << "\n";
            }
        }
    }

    [[nodiscard]] static NumType
        generate_random_numbers(NumType min = std::numeric_limits<NumType>::min(),
                                NumType max = std::numeric_limits<NumType>::max())
    {
        static std::mt19937_64 eng{
            static_cast<unsigned long>(
                std::chrono::system_clock::now().time_since_epoch().count()
            )
        };
        if constexpr (std::is_integral_v<NumType>){
            static std::uniform_int_distribution<NumType> distribution{min, max};
            return distribution(eng);
        } else {
            static std::uniform_real_distribution<NumType> distribution{min, max};
            return distribution(eng);
        }
    }

    [[nodiscard]] std::string
        compare(const std::bitset<total_algorithm_number>& algorithm_select
                = algorithms::all) const
    {
        std::ostringstream oss;
        oss << table_title();
        if (algorithm_select[0]){
            oss << table_horizontal_line('|')
                << table_row("selection", sorting_algorithms::selection_sort);
        }
        if (algorithm_select[1]){
            oss << table_horizontal_line('|')
                << table_row("bubble", sorting_algorithms::bubble_sort);
        }
        if (algorithm_select[2]){
            oss << table_horizontal_line('|')
                << table_row("quick", sorting_algorithms::quick_sort);
        }
        if (algorithm_select[3]){
            oss << table_horizontal_line('|')
                << table_row("merge", sorting_algorithms::merge_sort);
        }
        if (algorithm_select[4]){
            oss << table_horizontal_line('|')
                << table_row("insertion", sorting_algorithms::insertion_sort);
        }
        if (algorithm_select[5]){
            oss << table_horizontal_line('|')
                << table_row("heap", sorting_algorithms::heap_sort);
        }
        oss << table_horizontal_line('+');
        return oss.str();
    }

private:

    std::vector<NumType> m_vec;
    std::int64_t m_test_number{};
    std::int64_t m_input_size{};

    using algorithmSignature =
        void(std::vector<NumType>&, const std::int64_t&, std::uint64_t&, std::uint64_t&);

    static constexpr int table_columns[]{
        13, 16, 14, 21, 21, 25, 25,
        3, 2, 3, 3
    };

    enum class format {
        left, center, right
    };

    static void check_argumants(std::int64_t test_number,
                                std::int64_t input_size)
    {
        if (input_size <= 0){
            throw std::runtime_error{
                "input size cannot be zero or negative"
            };
        } else if (test_number <= 0){
            throw std::runtime_error{
                "test number cannot be zero or negative"
            };
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

    [[nodiscard]]
        static std::string table_column(const std::string& str,
                                        int column, const format& manip)
    {
        const auto length{std::ssize(str)};
        const auto max_length{table_columns[column]};
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
        return c + std::string(table_columns[0], '-') + c +
                   std::string(table_columns[1], '-') + c +
                   std::string(table_columns[2], '-') + c +
                   std::string(table_columns[3], '-') + c +
                   std::string(table_columns[4], '-') + c +
                   std::string(table_columns[5], '-') + c +
                   std::string(table_columns[6], '-') + c + "\n";
    }

    [[nodiscard]]
        std::string table_row(const std::string& name,
                              const std::function<algorithmSignature>& algorithm) const
    {
        static std::vector<std::int64_t> time_vec;
        std::uint64_t comparison{}, assignment{};
        time_vec.reserve(m_test_number);
        for (std::int64_t i{}; i < m_test_number; ++i){
            std::vector<NumType> temp(begin(m_vec), end(m_vec));
            auto start = std::chrono::steady_clock::now();
            algorithm(temp, m_input_size, comparison, assignment);
            auto end = std::chrono::steady_clock::now();
            using namespace std::chrono;
            microseconds time_interval{
                duration_cast<microseconds>(end - start)
            };
            time_vec.push_back(time_interval.count());
        }
        sort(begin(time_vec), end(time_vec));

        using namespace std::chrono;
        microseconds median_us{
            time_vec[m_test_number / 2]
        };
        milliseconds median_ms{
            duration_cast<milliseconds>(median_us % 1s)
        };
        seconds median_s{
            duration_cast<seconds>(median_us % 1min)
        };
        minutes median_min{
            duration_cast<minutes>(median_us)
        };
        median_us %= 1ms;

        microseconds avg_us{
            static_cast<std::int64_t>(
                accumulate(begin(time_vec), end(time_vec), 0.)/m_test_number
            )
        };
        milliseconds avg_ms{
            duration_cast<milliseconds>(avg_us % 1s)
        };
        seconds avg_s{
            duration_cast<seconds>(avg_us % 1min)
        };
        minutes avg_min{
            duration_cast<minutes>(avg_us)
        };
        avg_us %= 1ms;

        std::ostringstream median_time, avg_time;
        median_time << std::setw(table_columns[7])  << median_min.count() << "m "
                    << std::setw(table_columns[8])  << median_s.count()   << "s "
                    << std::setw(table_columns[9])  << median_ms.count()  << "ms "
                    << std::setw(table_columns[10]) << median_us.count()  << "us";

        avg_time << std::setw(table_columns[7])  << avg_min.count() << "m "
                 << std::setw(table_columns[8])  << avg_s.count()   << "s "
                 << std::setw(table_columns[9])  << avg_ms.count()  << "ms "
                 << std::setw(table_columns[10]) << avg_us.count()  << "us";

        std::ostringstream oss;
        oss << "|" << table_column(name                   , 0, format::center)
            << "|" << table_column(readable(m_input_size) , 1, format::right )
            << "|" << table_column(readable(m_test_number), 2, format::right )
            << "|" << table_column(readable(comparison)   , 3, format::right )
            << "|" << table_column(readable(assignment)   , 4, format::right )
            << "|" << table_column(median_time.str()      , 5, format::center)
            << "|" << table_column(avg_time.str()         , 6, format::center)
            << "|\n";
        time_vec.clear();
        return oss.str();
    }

    static void
        selection_sort(std::vector<NumType>& vec, const std::int64_t& size,
                       std::uint64_t& comparison, std::uint64_t& assignment)
    {
        for (std::int64_t i{}; i < size - 1; ++i){
            std::int64_t min{i};
            for (std::int64_t j{i + 1}; j < size; ++j){
                if (vec[j] < vec[min]){
                    ++comparison;
                    min = j;
                }
            }
            assignment += 2;
            std::swap(vec[i], vec[min]);
        }
    }

    static void
        bubble_sort(std::vector<NumType>& vec, const std::int64_t& size,
                    std::uint64_t& comparison, std::uint64_t& assignment)
    {
        for (std::int64_t i{}; i < size - 1; ++i){
            for (std::int64_t j{}; j < size - 1 - i; ++j){
                if (vec[j + 1] < vec[j]){
                    ++comparison;
                    assignment += 2;
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    }

    static void
        quick_sort(std::vector<NumType>& vec, const std::int64_t& size,
                   std::uint64_t& comparison, std::uint64_t& assignment)
    {
          quick_sort_helper_1(vec, 0, size - 1, comparison, assignment);
    }

    static void
        quick_sort_helper_1(std::vector<NumType>& vec, std::int64_t low, std::int64_t high,
                            std::uint64_t& comparison, std::uint64_t& assignment)
    {
        if (low < high){
            std::int64_t pi{
                quick_sort_helper_2(vec, low, high, comparison, assignment)
            };
            quick_sort_helper_1(vec, low, pi - 1, comparison, assignment);
            quick_sort_helper_1(vec, pi + 1, high, comparison, assignment);
        }
    }

    [[nodiscard]] static std::int64_t
        quick_sort_helper_2(std::vector<NumType>& vec, std::int64_t low, std::int64_t high,
                            std::uint64_t& comparison, std::uint64_t& assignment)
    {
        NumType pivot{vec[high]};
        std::int64_t i{low - 1};
        for (std::int64_t j{low}; j < high; ++j){
            if (vec[j] <= pivot){
                ++comparison;
                assignment += 2;
                i++;
                std::swap(vec[i], vec[j]);
            }
        }
        assignment += 2;
        std::swap(vec[i + 1], vec[high]);
        return (i + 1);
    }

    static void
        merge_sort(std::vector<NumType>& vec, const std::int64_t& size,
                   std::uint64_t& comparison, std::uint64_t& assignment)
    {
        merge_sort_helper_1(vec, 0, size - 1, comparison, assignment);
    }

    static void
    merge_sort_helper_1(std::vector<NumType>& vec, std::int64_t l, std::int64_t r,
                        std::uint64_t& comparison, std::uint64_t& assignment)
    {
        if (l < r) {
            std::int64_t m{l + (r - l) / 2};
            merge_sort_helper_1(vec, l, m, comparison, assignment);
            merge_sort_helper_1(vec, m + 1, r, comparison, assignment);
            merge_sort_helper_2(vec, l, m, r, comparison, assignment);
        }
    }

    static void
        merge_sort_helper_2(std::vector<NumType>& vec,
                            std::int64_t p, std::int64_t q, std::int64_t r,
                            std::uint64_t& comparison, std::uint64_t& assignment)
    {
        std::int64_t n1{q - p + 1};
        std::int64_t n2{r - q};
        std::vector<NumType> L, M;
        L.reserve(n1);
        M.reserve(n2);
        for (std::int64_t i{}; i < n1; ++i){
            L.push_back(vec[p + i]);
        }
        for (std::int64_t j{}; j < n2; ++j){
            M.push_back(vec[q + 1 + j]);
        }
        std::int64_t i{}, j{}, k{p};
        while (i < n1 && j < n2) {
            ++comparison;
            ++assignment;
            if (L[i] <= M[j]) {
                vec[k] = L[i];
                i++;
            } else {
                vec[k] = M[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            ++assignment;
            vec[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            ++assignment;
            vec[k] = M[j];
            j++;
            k++;
        }
    }

    static void
        insertion_sort(std::vector<NumType>& vec, const std::int64_t& size,
                       std::uint64_t& comparison, std::uint64_t& assignment)
    {
        for (std::int64_t i{1}; i < size; ++i) {
            NumType key{vec[i]};
            std::int64_t j{i - 1};
            while (key < vec[j] && j >= 0) {
                ++comparison;
                ++assignment;
                vec[j + 1] = vec[j];
                --j;
            }
            ++assignment;
            vec[j + 1] = key;
        }
    }

    static void
        heap_sort(std::vector<NumType>& vec, const std::int64_t& size,
                  std::uint64_t& comparison, std::uint64_t& assignment)
    {
        for (std::int64_t i{size / 2 - 1}; i >= 0; --i){
            heap_sort_helper(vec, size, i, comparison, assignment);
        }
        for (std::int64_t i{size - 1}; i >= 0; --i) {
            assignment += 2;
            std::swap(vec[0], vec[i]);
            heap_sort_helper(vec, i, 0, comparison, assignment);
        }
    }

    static void
        heap_sort_helper(std::vector<NumType>& vec, const std::int64_t& size, std::int64_t i,
                         std::uint64_t& comparison, std::uint64_t& assignment)
    {
        std::int64_t largest{i};
        std::int64_t left{2 * i + 1};
        std::int64_t right{2 * i + 2};
        if (left < size && vec[left] > vec[largest]){
            ++comparison;
            largest = left;
        }
        if (right < size && vec[right] > vec[largest]){
            ++comparison;
            largest = right;
        }
        if (largest != i) {
            assignment += 2;
            std::swap(vec[i], vec[largest]);
            heap_sort_helper(vec, size, largest, comparison, assignment);
        }
    }
};

} //namespace

#endif // SORTING_ALGORITHMS_HPP
