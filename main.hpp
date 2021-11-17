#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string_view>

#include <sorting_algorithms.hpp>

using T = int;

inline project::sorting_algorithms<T> algorithms;

inline const auto default_test_count{
    std::to_string(project::sorting_algorithms<T>::default_test_count)
};

inline const auto default_input_size{
    std::to_string(project::sorting_algorithms<T>::default_input_size)
};

inline const auto help_message{
    "sorting-algorithms\n"
    "a C++20 program to compare sorting algorithms\n\n"
    "usage;\n"
    "sorting-algorithms\n"
    "\tcompare sorting algorithms with " + default_input_size +
    " random numbers " + default_test_count + " times\n\n"
    "sorting-algorithms -h/--help\n"
    "\tprint this help message\n\n"
    "sorting-algorithms <input_size>\n"
    "\tcompare sorting algorithms with "
    "<input_size> random numbers " + default_test_count + " times\n\n"
    "sorting-algorithms <input_file>\n"
    "\tcompare sorting algorithms with "
    "reading numbers from <input_file> " + default_test_count + " times\n\n"
    "sorting-algorithms <input_size> <test_number>\n"
    "\tcompare sorting algorithms sort with "
    "<input_size> random numbers <test_number> times\n\n"
    "sorting-algorithms <input_file> <test_number>\n"
    "\tcompare sorting algorithms with "
    "reading numbers from <input_file> <test_number> times\n\n"
    "sorting-algorithms -gen/--generate <file_number>\n"
    "\tgenerate <file_number> files, each containing " +
    default_input_size + " random numbers\n\n"
    "sorting-algorithms -gen/--generate <file_number> <input_size>\n"
    "\tgenerate <file_number> files, each containing"
    " <input_size> random numbers\n\n"
    "\tthe filenames of the generated files are "
    "input<file_number>.txt by default\n\n"
    "author: Oğuz Toraman <oguz.toraman@protonmail.com> @2021"
};

inline bool is_number(const std::string_view& sv)
{
    return (sv.find_first_not_of("0123456789") == std::string::npos);
}

inline void check_argumants(const std::string& input_size_or_file)
{
    if ("-h"         == input_size_or_file ||
        "--help"     == input_size_or_file ||
        "-gen"       == input_size_or_file ||
        "--generate" == input_size_or_file){
        throw std::runtime_error{help_message};
    } else if (!is_number(input_size_or_file)){
        algorithms.set(input_size_or_file);
    } else {
        algorithms.set(std::stoll(input_size_or_file));
    }
}

inline void check_argumants(const std::string& input_size_or_file,
                     const std::string& file_number_or_test_number, bool& compare)
{
    if ("-gen"       == input_size_or_file ||
        "--generate" == input_size_or_file){
        if (is_number(file_number_or_test_number)){
            compare = false;
            project::sorting_algorithms<T>::generate_input_files(
                project::sorting_algorithms<T>::default_input_size,
                std::stoll(file_number_or_test_number)
            );
            std::cout << "generated " << file_number_or_test_number
                      << " files, each containing "
                      << default_input_size
                      << " random inputs\n";
        } else {
            throw std::runtime_error{help_message};
        }
    } else if (is_number(file_number_or_test_number)){
        if (!is_number(input_size_or_file)){
            algorithms.set(
                input_size_or_file,
                std::stoll(file_number_or_test_number)
            );
        } else {
            algorithms.set(
                std::stoll(input_size_or_file),
                std::stoll(file_number_or_test_number)
            );
        }
    } else {
        throw std::runtime_error{help_message};
    }
}

inline void check_argumants(const std::string& input_size_or_file,
                     const std::string& file_number_or_test_number,
                     const std::string& input_size, bool& compare)
{
    if ("-gen"       == input_size_or_file ||
        "--generate" == input_size_or_file){
        if (is_number(file_number_or_test_number) && is_number(input_size)){
            compare = false;
            project::sorting_algorithms<T>::generate_input_files(
                std::stoll(input_size),
                std::stoll(file_number_or_test_number)
            );
            std::cout << "generated " << file_number_or_test_number
                      << " files, each containing "
                      << input_size << " random inputs\n";
        } else {
            throw std::runtime_error{help_message};
        }
    } else {
        throw std::runtime_error{help_message};
    }
}

#endif // MAIN_HPP