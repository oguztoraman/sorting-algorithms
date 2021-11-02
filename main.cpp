#include <iostream>
#include <string_view>

#include <sorting_algorithms.hpp>

using T = int;

using namespace project;

const auto default_test_number{
    std::to_string(sorting_algorithms<T>::default_test_number)
};

const auto default_input_size{
    std::to_string(sorting_algorithms<T>::default_input_size)
};

const auto help_message{
    "sorting-algorithms\n"
    "a C++20 program to compare sorting algorithms\n\n"
    "usage;\n"
    "sorting-algorithms\n"
    "\tcompare sorting algorithms with " + default_input_size +
    " random numbers " + default_test_number + " times\n\n"
    "sorting-algorithms -h/--help\n"
    "\tprint this help message\n\n"
    "sorting-algorithms <input_size>\n"
    "\tcompare sorting algorithms with "
    "<input_size> random numbers " + default_test_number + " times\n\n"
    "sorting-algorithms <input_file>\n"
    "\tcompare sorting algorithms with "
    "reading numbers from <input_file> " + default_test_number + " times\n\n"
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

bool is_number(const std::string_view& sv)
{
    return (sv.find_first_not_of("0123456789") == std::string::npos);
}

int main(int argc, char *argv[])
{
    try {
        bool compare{true};
        bool throw_help_message{false};
        sorting_algorithms<T> algorithms;
        switch (argc){
        case 1 : break;
        case 2 : {
            const std::string input_size_or_file{argv[1]};
            if ("-h"         == input_size_or_file ||
                "--help"     == input_size_or_file ||
                "-gen"       == input_size_or_file ||
                "--generate" == input_size_or_file){
                throw_help_message = true;
            } else if (!is_number(input_size_or_file)){
                algorithms.set(input_size_or_file);
            } else {
                algorithms.set(std::stoll(input_size_or_file));
            }
            break;
        }
        case 3 : {
            if ("-gen"       == std::string{argv[1]} ||
                "--generate" == std::string{argv[1]}){
                const std::string file_number{argv[2]};
                if (is_number(file_number)){
                    compare = false;
                    sorting_algorithms<T>::generate_input_files(
                        sorting_algorithms<T>::default_input_size,
                        std::stoll(file_number)
                    );
                    std::cout << "generated " << file_number
                              << " files, each containing "
                              << default_input_size
                              << " random inputs\n";
                } else {
                    throw_help_message = true;
                }
            } else if (const std::string test_number{argv[2]};
                       is_number(test_number)){
                const std::string input_size_or_file{argv[1]};
                if (!is_number(input_size_or_file)){
                    algorithms.set(
                        input_size_or_file,
                        std::stoll(test_number)
                    );
                } else {
                    algorithms.set(
                        std::stoul(input_size_or_file),
                        std::stoll(test_number)
                    );
                }
            } else {
                throw_help_message = true;
            }
            break;
        }
        case 4 : {
            if ("-gen"       == std::string{argv[1]} ||
                "--generate" == std::string{argv[1]}){
                const std::string file_number{argv[2]}, input_size{argv[3]};
                if (is_number(file_number) && is_number(input_size)){
                    compare = false;
                    sorting_algorithms<T>::generate_input_files(
                        std::stoll(input_size),
                        std::stoll(file_number)
                    );
                    std::cout << "generated " << file_number
                              << " files, each containing "
                              << input_size << " random inputs\n";
                } else {
                    throw_help_message = true;
                }
            } else {
                throw_help_message = true;
            }
            break;
        }
        default: throw_help_message = true;
        }
        if (throw_help_message){
            throw std::runtime_error{help_message};
        }
        if (compare){
            std::cout << algorithms.compare(
                sorting_algorithms<T>::all
            );
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
