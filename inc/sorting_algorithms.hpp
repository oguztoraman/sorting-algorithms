/* SPDX-FileCopyrightText: Copyright (c) 2022-2024 Oğuz Toraman <oguz.toraman@tutanota.com> */
/* SPDX-License-Identifier: BSL-1.0 */

#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <bitset>
#include <vector>
#include <chrono>
#include <random>
#include <limits>
#include <fstream>
#include <functional>

#include <algorithm_concepts.hpp>
#include <algorithm_comparison_table.hpp>

namespace algorithms {

template <algorithm_value_type ValueType = int>
class sorting_algorithms {
public:
    static constexpr std::size_t sorting_algorithm_count = 6;
    static constexpr std::int64_t default_output_file_count = 5;
    static constexpr std::int64_t default_test_count = 21;
    static constexpr std::int64_t default_input_size = 5'000;

    enum algorithms {
        selection = 1L << 0,
        bubble 	  = 1L << 1,
        quick     = 1L << 2,
        merge     = 1L << 3,
        insertion = 1L << 4,
        heap      = 1L << 5,

        all       = (1L << sorting_algorithm_count) - 1
    };

    sorting_algorithms()
        : sorting_algorithms(default_input_size, default_test_count) { }

    template <algorithm_container Container>
    requires std::same_as<typename Container::value_type, ValueType>
    sorting_algorithms(const Container& c, std::int64_t test_count = default_test_count)
        : m_vec{begin(c), end(c)},
        m_test_count{test_count},
        m_input_size{std::ssize(m_vec)}
    {
        check_argumants(m_test_count, m_input_size);
    }

    sorting_algorithms(std::int64_t input_size,
                       std::int64_t test_count = default_test_count)
        : m_test_count{test_count},
        m_input_size{input_size}
    {
        check_argumants(m_test_count, m_input_size);
        m_vec.reserve(m_input_size);
        generate_n(back_inserter(m_vec), m_input_size,
            [](){ return sorting_algorithms::generate_random_numbers(); }
        );
    }

    sorting_algorithms(const std::string& file_name,
                       std::int64_t test_count = default_test_count)
        : m_test_count{test_count}
    {
        m_vec.reserve(default_input_size);
        std::ifstream file{file_name};
        if (!file){
            throw std::runtime_error{"failed to open " + file_name};
        }
        ValueType input{};
        while(file >> input){
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
    const std::vector<ValueType>& get_inputs() const & noexcept
    {
        return m_vec;
    }

    [[nodiscard]]
    std::vector<ValueType>& get_inputs() & noexcept
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
        sorting_algorithms& operator=(const Container& c)
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
        m_vec = std::move(std::vector<ValueType>{begin(c), end(c)});
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
            [](){ return sorting_algorithms::generate_random_numbers(); }
        );
    }

    void set(const std::string& file_name,
             std::int64_t test_count = default_test_count)
    {
        m_vec.clear();
        m_vec.reserve(default_input_size);
        m_test_count = test_count;
        std::ifstream file{file_name};
        if (!file){
            throw std::runtime_error{"failed to open " + file_name};
        }
        ValueType input{};
        while(file >> input){
            m_vec.push_back(input);
        }
        m_vec.shrink_to_fit();
        m_input_size = std::ssize(m_vec);
        check_argumants(m_test_count, m_input_size);
    }

    static void
    generate_input_files(std::int64_t input_size = default_input_size,
                         std::int64_t output_file_count = default_output_file_count,
                         ValueType min = std::numeric_limits<ValueType>::min(),
                         ValueType max = std::numeric_limits<ValueType>::max())
    {
        for (std::int64_t i{1}; i <= output_file_count; ++i){
            std::ofstream file{"input" + std::to_string(i) + ".txt"};
            if (!file){
                throw std::runtime_error{
                    "failed to create input" + std::to_string(i) + ".txt"
                };
            }
            for (std::int64_t j{}; j < input_size; ++j){
                file << sorting_algorithms::generate_random_numbers(min, max) << "\n";
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

    [[nodiscard]] std::string
        compare(const std::bitset<sorting_algorithm_count>& algorithm_select
                = algorithms::all)
    {
        m_comparison_table.add_title();
        for (std::size_t i{}; i < sorting_algorithm_count; ++i){
            if (algorithm_select[i]){
                m_comparison_table.add_row(perform_test(m_algorithms[i]));
            }
        }
        m_comparison_table.add_table_separator_line();
        return m_comparison_table.get_table();
    }

private:
    std::vector<ValueType> m_vec;
    std::int64_t m_test_count{};
    std::int64_t m_input_size{};
    algorithm_comparison_table m_comparison_table{};

    using table = algorithm_comparison_table;

    using algorithm_signature_t = void(*)(
        std::vector<ValueType>&,
        const table::input_size_t&,
        table::comparison_count_t&,
        table::assignment_count_t&
    );

    using algorithm_pair_t = std::pair<
        table::algorithm_name_t,
        algorithm_signature_t
    >;

    std::array<algorithm_pair_t, sorting_algorithm_count> m_algorithms{
        std::make_pair("selection", sorting_algorithms::selection_sort),
        std::make_pair("buble", sorting_algorithms::bubble_sort),
        std::make_pair("quick", sorting_algorithms::quick_sort),
        std::make_pair("merge", sorting_algorithms::merge_sort),
        std::make_pair("insertion", sorting_algorithms::insertion_sort),
        std::make_pair("heap", sorting_algorithms::heap_sort)
    };

    void check_argumants(std::int64_t test_count, std::int64_t input_size) const
    {
        if (input_size <= 0){
            throw std::runtime_error{"input size cannot be zero or negative"};
        }
        if (static_cast<std::size_t>(input_size) > m_vec.max_size()){
            throw std::runtime_error{
                "input size cannot be greater than " + table::readable(m_vec.max_size())
            };
        }
        if (test_count <= 0){
            throw std::runtime_error{"test count cannot be zero or negative"};
        }
        if (static_cast<std::size_t>(test_count) > m_vec.max_size()){
            throw std::runtime_error{
                "test count cannot be greater than " + table::readable(m_vec.max_size())
            };
        }
    }

    [[nodiscard]] table::test_results_t
        perform_test(const algorithm_pair_t& algorithm) const
    {
        auto algorithm_function = std::get<algorithm_signature_t>(algorithm);
        auto algorithm_name = std::get<table::algorithm_name_t>(algorithm);
        static std::vector<std::int64_t> time_vec;
        std::uint64_t comparison{}, assignment{};
        time_vec.reserve(m_test_count);
        for (std::int64_t i{}; i < m_test_count; ++i){
            std::vector<ValueType> temp(begin(m_vec), end(m_vec));
            auto start = std::chrono::steady_clock::now();
            std::invoke(algorithm_function, temp, m_input_size, comparison, assignment);
            auto end = std::chrono::steady_clock::now();
            table::us_t time_interval{
                std::chrono::duration_cast<table::us_t>(end - start)
            };
            time_vec.push_back(time_interval.count());
        }
        sort(begin(time_vec), end(time_vec));
        table::us_t median_us{time_vec[m_test_count / 2]};
        table::us_t average_us{static_cast<std::int64_t>(
            accumulate(begin(time_vec), end(time_vec), 0.)/m_test_count
        )};
        time_vec.clear();
        comparison /= m_test_count, assignment /= m_test_count;
        return std::make_tuple(
            algorithm_name, m_input_size, m_test_count,
            comparison, assignment, median_us, average_us
        );
    }

    static void
        selection_sort(std::vector<ValueType>& vec, const std::int64_t& size,
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
        bubble_sort(std::vector<ValueType>& vec, const std::int64_t& size,
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
        quick_sort(std::vector<ValueType>& vec, const std::int64_t& size,
                   std::uint64_t& comparison, std::uint64_t& assignment)
    {
          quick_sort_helper_1(vec, 0, size - 1, comparison, assignment);
    }

    static void
        quick_sort_helper_1(
            std::vector<ValueType>& vec, std::int64_t low, std::int64_t high,
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
        quick_sort_helper_2(
            std::vector<ValueType>& vec, std::int64_t low, std::int64_t high,
            std::uint64_t& comparison, std::uint64_t& assignment)
    {
        ValueType pivot{vec[high]};
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
        merge_sort(std::vector<ValueType>& vec, const std::int64_t& size,
                   std::uint64_t& comparison, std::uint64_t& assignment)
    {
        merge_sort_helper_1(vec, 0, size - 1, comparison, assignment);
    }

    static void
        merge_sort_helper_1(
            std::vector<ValueType>& vec, std::int64_t l, std::int64_t r,
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
        merge_sort_helper_2(std::vector<ValueType>& vec,
                            std::int64_t p, std::int64_t q, std::int64_t r,
                            std::uint64_t& comparison, std::uint64_t& assignment)
    {
        std::int64_t n1{q - p + 1};
        std::int64_t n2{r - q};
        std::vector<ValueType> L, M;
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
        insertion_sort(std::vector<ValueType>& vec, const std::int64_t& size,
                       std::uint64_t& comparison, std::uint64_t& assignment)
    {
        for (std::int64_t i{1}; i < size; ++i) {
            ValueType key{vec[i]};
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
        heap_sort(std::vector<ValueType>& vec, const std::int64_t& size,
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
        heap_sort_helper(
            std::vector<ValueType>& vec, const std::int64_t& size, std::int64_t i,
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

} /* namespace algorithms */

#endif /* SORTING_ALGORITHMS_HPP */
