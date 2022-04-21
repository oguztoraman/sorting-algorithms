/*
 * main.cpp
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

#include <main.hpp>

using namespace project;

int main(int argc, char *argv[])
{
    try {
        bool compare{true};
        switch (argc){
        case 1 : break;
        case 2 : check_argumants_and_assign(argv[1]); break;
        case 3 : check_argumants_and_assign(argv[1], argv[2], compare); break;
        case 4 : check_argumants_and_assign(argv[1], argv[2], argv[3], compare); break;
        default: throw std::runtime_error{help_message};
        }
        if (compare){
            std::cout << algorithms.compare(algorithms.bubble | algorithms.heap);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
