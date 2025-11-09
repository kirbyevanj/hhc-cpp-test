#include <gtest/gtest.h>

#include "hhc.hpp"
#include "hhc_constants.hpp"

#include <array>
#include <cstddef>

/**
 * @file unpad_tests.cpp
 * @brief Unit tests covering the HHC string unpadding helper.
 */

namespace {

constexpr char kPad = hhc::ALPHABET[0];

}  // namespace

TEST(HhcUnpadStringTest, ReplacesLeadingPaddingWithSpaces) {
    std::array<char, hhc::HHC_32BIT_STRING_LENGTH> buffer{
        kPad, kPad, kPad, 'A', 'B', 'C', 'D', '\0'};

    hhc::hhc_unpad_string(buffer.data());

    // After unpadding, the non-padded content is moved to the beginning and null-terminated
    EXPECT_STREQ(buffer.data(), "ABCD");
    EXPECT_EQ(buffer[4], '\0');
}

TEST(HhcUnpadStringTest, StopsAtFirstNonPaddingCharacter) {
    std::array<char, hhc::HHC_32BIT_STRING_LENGTH> buffer{
        '.', 'A', 'B', 'C', 'D', 'E', 'F', '\0'};

    hhc::hhc_unpad_string(buffer.data());

    EXPECT_EQ(buffer[0], '.');
    EXPECT_EQ(buffer[1], 'A');
}

TEST(HhcUnpadStringTest, ConvertsAllPaddingCharactersToSpaces) {
    std::array<char, hhc::HHC_32BIT_STRING_LENGTH> buffer{
        kPad, kPad, kPad, kPad, kPad, kPad, 'X', '\0'};

    hhc::hhc_unpad_string(buffer.data());

    // After unpadding, only the non-padded character remains at the beginning
    EXPECT_STREQ(buffer.data(), "X");
    EXPECT_EQ(buffer[1], '\0');
}

