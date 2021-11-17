#include "main.hpp"

using namespace project;

int main(int argc, char *argv[])
{
    try {
        bool compare{true};
        switch (argc){
        case 1 : break;
        case 2 : check_argumants(argv[1]); break;
        case 3 : check_argumants(argv[1], argv[2], compare); break;
        case 4 : check_argumants(argv[1], argv[2], argv[3], compare); break;
        default: throw std::runtime_error{help_message};
        }
        if (compare){
            std::cout << algorithms.compare();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
