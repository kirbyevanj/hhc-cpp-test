#ifndef hhc_HPP
#define hhc_HPP
#include <cstdint>
#include <cassert>
#include <array>
#include <cmath>
#include <cstdio>
#define BASE 66

namespace hhc {
    constexpr uint32_t BITS_PER_BYTE = 8;
    constexpr std::array<char, BASE> HHC_ALPHABET = {
        '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', '_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
        'v', 'w', 'x', 'y', 'z', '~'
    };
    constexpr char HHC_LAST_LETTER = HHC_ALPHABET[BASE - 1];

    constexpr std::array<uint32_t, HHC_LAST_LETTER+1> make_hhc_inverse_alphabet() {
        std::array<uint32_t, HHC_LAST_LETTER+1> inverse_alphabet{};
        for (int i = 0; i < BASE; i++) {
            inverse_alphabet[HHC_ALPHABET[i]] = i;
        }
        return inverse_alphabet;
    }
    constexpr auto HHC_INVERSE_ALPHABET = make_hhc_inverse_alphabet();

    constexpr void hhc_32bit_encode_iter(uint32_t& input, uint64_t* output, int n_iter) {
        const uint32_t index = input % BASE;
        input /= BASE;

        *output ^= static_cast<uint64_t>(HHC_ALPHABET[index]) << (BITS_PER_BYTE * n_iter);
    }

    /**
     * @brief Encode a 32-bit integer into an 8-character string
     * @param input The 32-bit integer to encode
     * @param output_string The output string to write the encoded result to
     */
    constexpr void hhc_32bit_encode(uint32_t input, char* output_string) {
        assert(output_string != nullptr);
        auto* output = reinterpret_cast<uint64_t*>(output_string);

        constexpr int N_ITERS = 8;
        for (int iter = N_ITERS-1; iter >= 0; iter--) {
            hhc_32bit_encode_iter(input, output, iter);
        }
    }

    constexpr uint32_t hhc_32bit_decode(const char* input_string) {
        assert(input_string != nullptr);
        uint32_t output = 0;

        constexpr int N_ITERS = 8;
        uint32_t exponent = 1;
        for (int iter = 7; iter >= 0; --iter) {
            const uint32_t index = HHC_INVERSE_ALPHABET[input_string[iter]];
            //std::printf("index: %u, exponent: %u, output: %u\n", index, exponent, output);
            output += index * exponent;
            exponent *= BASE;
        }
        //std::printf("output: %u\n", output);
        return output;
    }
} // namespace hhc

#endif // hhc_HPP
