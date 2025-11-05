#ifndef HCC_HPP
#define HCC_HPP
#include <cstdint>
#include <cassert>
#include <array>
#define BASE 66

namespace hcc {
    struct __ShortString32 {
        uint32_t data;
        uint32_t __padding;
    };
    struct ShortString32 {
        char data[4];
        uint32_t __padding;
    };

    union ShortStringUnion32 {
        __ShortString32 __short_string;
        ShortString32 short_string;
    };

    struct __ShortString64 {
        uint64_t data;
        uint64_t __padding;
    };
    struct ShortString64 {
        char data[8];
        uint64_t __padding;
    };

    union ShortStringUnion64 {
        __ShortString64 __short_string;
        ShortString64 short_string;
    };

    constexpr std::array<char, BASE> HHC_ALPHABET = {
        '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', '_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
        'v', 'w', 'x', 'y', 'z', '~'
    };
        // Encode function
    inline void hcc_encode() {
        // TODO: Implement encoding logic
    }

    // Decode function
    inline void hcc_decode() {
        // TODO: Implement decoding logic
    }

    inline void hcc_32bit_iter(uint32_t& input, uint64_t* output, uint32_t n_iter) {
        const uint32_t index = input % BASE;
        input /= BASE;
        *output ^= static_cast<uint64_t>(HHC_ALPHABET[index]) << (8 * (n_iter));
    }

    // 32-bit encode function
    inline void hcc_32bit_encode(uint32_t input, char* output_string) {
        assert(output_string != nullptr);
        uint64_t* output = reinterpret_cast<uint64_t*>(output_string);

        hcc_32bit_iter(input, output, 7);
        hcc_32bit_iter(input, output, 6);
        hcc_32bit_iter(input, output, 5);
        hcc_32bit_iter(input, output, 4);
        hcc_32bit_iter(input, output, 3);
        hcc_32bit_iter(input, output, 2);
        hcc_32bit_iter(input, output, 1);
        hcc_32bit_iter(input, output, 0);

        //ShortStringUnion64 short_string_union;
        //short_string_union.__short_string.data = *output;
        //short_string_union.__short_string.__padding = 0;

        //printf("output: %s\n", short_string_union.short_string.data);
    }

    // 32-bit decode function
    inline void hcc_32bit_decode() {
        // TODO: Implement 32-bit decoding logic
    }

    // 64-bit encode function
    inline void hcc_64bit_encode() {
        // TODO: Implement 64-bit encoding logic
    }

    // 64-bit decode function
    inline void hcc_64bit_decode() {
        // TODO: Implement 64-bit decoding logic
    }

} // namespace hcc

#endif // HCC_HPP
