/* SPDX-FileCopyrightText: Copyright (c) 2022-2024 Oğuz Toraman <oguz.toraman@tutanota.com> */
/* SPDX-License-Identifier: BSL-1.0 */

#include <cstdlib>
#include <iostream>
#include <sorting_algorithms.hpp>
#include <boost/program_options.hpp>

using T = int;
using namespace algorithms;
namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    try {
        std::string_view program{
            "sorting-algorithms\n"
            "A C++20 program to compare sorting algorithms."
        };
        std::string usage{
            "Usage: sorting-algorithms [OPTION]..."
        };
        std::string_view version{"sorting-algorithms v1.0.1"};
        std::string_view url{"https://github.com/oguztoraman/sorting-algorithms"};
        std::string_view license{
            "Copyright Oğuz Toraman 2022-2024.\n"
            "Distributed under the Boost Software License, Version 1.0.\n"
            "(See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)"
        };
        std::string_view author{"Written by Oğuz Toraman, oguz.toraman@tutanota.com"};

        sorting_algorithms<T> algorithms;
        std::string input_size, test_count, input_file;
        po::options_description command_line_options(usage);
        command_line_options.add_options()
            ("help,h", "display this help message")
            ("version,v", "display version")
            ("input-size", po::value<std::string>(&input_size)->default_value(
                 std::to_string(algorithms.default_input_size)), "the number of randomly generated inputs to be sorted")
            ("input-file", po::value<std::string>(&input_file), "read inputs from a file")
            ("test-count", po::value<std::string>(&test_count)->default_value(
                 std::to_string(algorithms.default_test_count)), "how many times to perform sorting per algorithm")
            ("generate", po::value<std::string>(), "the number of files each containing randomly generated inputs")
        ;
        po::variables_map variables_map;
        po::store(po::parse_command_line(argc, argv, command_line_options), variables_map);
        po::notify(variables_map);
        if (variables_map.count("help")){
            std::cout << program              << '\n' << '\n'
                      << command_line_options << '\n'
                      << version << '\n'
                      << url     << '\n' << '\n'
                      << license << '\n' << '\n'
                      << author  << '\n';
            return EXIT_SUCCESS;
        }
        if (variables_map.count("version")){
            std::cout << version << '\n'
                      << url     << '\n' << '\n'
                      << license << '\n' << '\n'
                      << author  << '\n';
            return EXIT_SUCCESS;
        }
        auto std_int64_t_max{std::to_string(std::numeric_limits<std::int64_t>::max())};
        if (input_size.length() > std_int64_t_max.length()){
            throw std::runtime_error{
                "input size cannot be grater than " + algorithm_comparison_table::readable(std_int64_t_max)
            };
        }
        if (test_count.length() > std_int64_t_max.length()){
            throw std::runtime_error{
                "test count cannot be grater than " + algorithm_comparison_table::readable(std_int64_t_max)
            };
        }
        if (variables_map.count("generate")){
            auto output_file_count{variables_map["generate"].as<std::string>()};
            if (output_file_count.length() > std_int64_t_max.length()){
                throw std::runtime_error{
                    "cannot be generate more than " + algorithm_comparison_table::readable(std_int64_t_max) + " files"
                };
            }
            std::cout << "generating "
                      << algorithm_comparison_table::readable(output_file_count)
                      << " files, each containing "
                      << algorithm_comparison_table::readable(input_size)
                      << " random inputs, please wait...\n"
            ;
            sorting_algorithms<T>::generate_input_files(std::stol(input_size), std::stol(output_file_count));
            std::cout << "generated "
                      << algorithm_comparison_table::readable(output_file_count)
                      << " files, each containing "
                      << algorithm_comparison_table::readable(input_size)
                      << " random inputs.\n"
            ;
            return EXIT_SUCCESS;
        }
        if (variables_map.count("input-file")){
            algorithms.set(input_file, std::stol(test_count));
            input_size = std::to_string(algorithms.get_input_size());
        } else {
            algorithms.set(std::stol(input_size), std::stol(test_count));
        }
        std::cout << "sorting algorithms are comparing for "
                  << algorithm_comparison_table::readable(input_size)
                  << " inputs, each sorting is performing "
                  << algorithm_comparison_table::readable(test_count)
                  << " times per algorithm, please wait...\n"
        ;
        std::cout << algorithms.compare(algorithms.all);
    } catch (const std::bad_alloc& e) {
        std::cerr << "there is not enough free memory to run sorting-algorithms\n";
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
