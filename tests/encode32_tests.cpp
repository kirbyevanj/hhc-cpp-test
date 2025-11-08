#include <gtest/gtest.h>
#include "hhc.hpp"

#include <cstdint>
#include <limits>
#include <string>
#include <string_view>

/**
 * @file encode32_tests.cpp
 * @brief Unit tests covering 32-bit encoding helpers.
 */

namespace {

constexpr auto U32_MAX_VALUE = std::numeric_limits<uint32_t>::max();
constexpr auto U32_MIN_VALUE = std::numeric_limits<uint32_t>::min();

using hhc::hhc_32bit_encode_padded;
using hhc::hhc_32bit_encode_unpadded;
using hhc::HHC_32BIT_STRING_LENGTH;

}  // namespace

TEST(HhcEncode32Test, Encode32BitTestUINT32_MIN) {
    std::string output(HHC_32BIT_STRING_LENGTH, '\0');
    hhc_32bit_encode_padded(U32_MIN_VALUE, output.data());
    EXPECT_STREQ(output.c_str(), "------");
}

TEST(HhcEncode32Test, Encode32BitTestUINT32_MAX) {
    std::string output(HHC_32BIT_STRING_LENGTH, '\0');
    hhc_32bit_encode_padded(U32_MAX_VALUE, output.data());
    EXPECT_STREQ(output.c_str(), "1QLCp1");
}

TEST(HhcEncode32Test, Encode32BitUnpaddedZeroProducesSpaces) {
    std::string output(HHC_32BIT_STRING_LENGTH, '\0');
    hhc_32bit_encode_unpadded(U32_MIN_VALUE, output.data());
    std::string_view unpadded(output.data(), hhc::HHC_32BIT_ENCODED_LENGTH);
    EXPECT_EQ(unpadded, std::string(hhc::HHC_32BIT_ENCODED_LENGTH, ' '));
}

TEST(HhcEncode32Test, Encode32BitUnpaddedPreservesSignificantDigits) {
    std::string output(HHC_32BIT_STRING_LENGTH, '\0');
    constexpr uint32_t kValue = 1;
    hhc_32bit_encode_unpadded(kValue, output.data());
    std::string_view unpadded(output.data(), hhc::HHC_32BIT_ENCODED_LENGTH);
    EXPECT_EQ(unpadded, "     .");
}

TEST(HhcEncode32Test, Encode32BitUnpaddedMaxRemainsUnchanged) {
    std::string output(HHC_32BIT_STRING_LENGTH, '\0');
    hhc_32bit_encode_unpadded(U32_MAX_VALUE, output.data());
    std::string_view unpadded(output.data(), hhc::HHC_32BIT_ENCODED_LENGTH);
    EXPECT_EQ(unpadded, "1QLCp1");
}

