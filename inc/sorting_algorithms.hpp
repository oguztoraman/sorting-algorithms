#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <algorithm_base.hpp>

namespace project {

static constexpr std::size_t sorting_algorithm_count = 6;

template <algorithm_value_type ValueType = int>
class sorting_algorithms
        : public algorithm_base<ValueType, sorting_algorithm_count> {
public:
    enum algorithms {
        selection = 1L << 0,
        bubble 	  = 1L << 1,
        quick     = 1L << 2,
        merge     = 1L << 3,
        insertion = 1L << 4,
        heap      = 1L << 5,

        all       = (1L << sorting_algorithm_count) - 1
    };

    using base = algorithm_base<ValueType, sorting_algorithm_count>;

    sorting_algorithms() = default;

    template <algorithm_container Container>
    requires std::same_as<typename Container::value_type, ValueType>
    sorting_algorithms(const Container& c,
                       std::int64_t test_count = base::default_test_count)
        : base::algorithm_base(c, test_count)          { }

    sorting_algorithms(std::int64_t input_size,
                       std::int64_t test_count = base::default_test_count)
        : base::algorithm_base{input_size, test_count} { }

    [[nodiscard]] std::string
        compare(const std::bitset<sorting_algorithm_count>& algorithm_select
                = algorithms::all) const
    {
        return base::compare_impl(algorithm_select, algorithm_names, functions);
    }

private:
    constexpr static const char* algorithm_names[] = {
        "selection", "bubble", "quick", "merge", "insertion", "heap"
    };

    constexpr static typename sorting_algorithms::algorithmSignature* functions[]{
        sorting_algorithms::selection_sort,
        sorting_algorithms::bubble_sort,
        sorting_algorithms::quick_sort,
        sorting_algorithms::merge_sort,
        sorting_algorithms::insertion_sort,
        sorting_algorithms::heap_sort
    };

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

} //namespace project

#endif // SORTING_ALGORITHMS_HPP
