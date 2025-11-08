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

    EXPECT_EQ(buffer[0], ' ');
    EXPECT_EQ(buffer[1], ' ');
    EXPECT_EQ(buffer[2], ' ');
    EXPECT_EQ(buffer[3], 'A');
    EXPECT_EQ(buffer[4], 'B');
    EXPECT_EQ(buffer[5], 'C');
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

    for (std::size_t i = 0; i < hhc::HHC_32BIT_ENCODED_LENGTH; ++i) {
        EXPECT_EQ(buffer[i], ' ') << "Index " << i << " was not unpadded";
    }
    EXPECT_EQ(buffer[hhc::HHC_32BIT_ENCODED_LENGTH], 'X');
}

