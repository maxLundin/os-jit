//
// Created by max on 11.04.19.
//

#pragma once

namespace jit {
    namespace function {

        int function() {
            volatile const int first = 2;
            volatile const int second = 2;
            return first + second;
        }


        const unsigned char code[] = {0x55, 0x48, 0x89, 0xe5, 0xc7, 0x45, 0xf8,
                /* first */ 0x02, 0x00, 0x00, 0x00,
                                      0xc7, 0x45, 0xfc,
                /* second */ 0x02, 0x00, 0x00, 0x00,
                                      0x8b, 0x55, 0xf8, 0x8b, 0x45, 0xfc, 0x01, 0xd0, 0x5d, 0xc3};

        const size_t code_size = sizeof(code);
        const size_t modify_a = 7;
        const size_t modify_b = 14;
    }
}
