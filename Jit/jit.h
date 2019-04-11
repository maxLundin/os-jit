//
// Created by max on 4/2/19.
//

#include "my_function.h"

namespace jit {

    class function_handler {
    public:
        function_handler(const unsigned char code[], size_t code_size, size_t modify_a, size_t modify_b,
                         int &return_code) {
            this->func_ptr = mmap(
                    nullptr,
                    code_size,
                    PROT_WRITE | PROT_READ,
                    MAP_PRIVATE | MAP_ANONYMOUS,
                    -1, 0);

            this->func_size = code_size;
            this->modify_a = modify_a;
            this->modify_b = modify_b;
            if (func_ptr == MAP_FAILED) {
                std::cerr << "Unable to allocate memory for the function: " << strerror(errno) << std::endl;
                return_code = -1;
                return;
            }
            std::memcpy(func_ptr, code, code_size);
            return_code = 0;
        }

        int mod(int a, int b) {
            if (mprotect(func_ptr, func_size, PROT_READ | PROT_WRITE) == -1) {
                std::cerr << "Can't change priviliges: " << strerror(errno) << "\n";
                return -1;
            }
            for (int i = 0; i < 4; ++i) {
                ((unsigned char *) func_ptr)[modify_a + i] = static_cast<unsigned char>(a);
                ((unsigned char *) func_ptr)[modify_b + i] = static_cast<unsigned char>(b);
                a >>= 8;
                b >>= 8;
            }
            return 0;
        }

        int run() {
            if (mprotect(func_ptr, func_size, PROT_EXEC | PROT_READ) == -1) {
                std::cerr << "Unable to set protection on a memory of function: " << strerror(errno) << std::endl;
                return -1;
            }
            std::cout << ((int (*)()) func_ptr)() << std::endl;
            return 0;
        }

        ~function_handler() {
            if (munmap(func_ptr, func_size) == -1) {
                std::cerr << "Unable to delete the mapping for the memory of function: " << strerror(errno)
                          << std::endl;
            }
        }

    private:
        void *func_ptr = nullptr;
        size_t func_size;
        size_t modify_a;
        size_t modify_b;
    };

}
