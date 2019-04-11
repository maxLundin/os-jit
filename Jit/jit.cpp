//
// Created by max on 4/2/19.
//

#include <sys/mman.h>
#include <iostream>
#include <cstring>
#include <string.h>

#include "jit.h"


int main() {
    int ret;
    jit::function_handler func(jit::function::code, jit::function::code_size, jit::function::modify_a,
                               jit::function::modify_b, ret);
    if (-1 == ret) {
        std::cerr << "Aborting..." << std::endl;
        exit(0);
    }

    while (true) {
        std::string input;
        std::cin >> input;
        if (input == "exit" || input == "break") {
            std::cout << "exiting..." << std::endl;
            break;
        }
        if (input == "execute" || input == "exec" || input == "run") {
            func.run();
        }
        if (input == "modify" || input == "mod") {
            int a, b;
            std::cout << "Enter \"a\" value" << std::endl;
            std::cin >> a;
            std::cout << "Enter \"b\" value" << std::endl;
            std::cin >> b;
            func.mod(a, b);
        }
    }
    return 0;
}