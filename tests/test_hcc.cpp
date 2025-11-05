#include <gtest/gtest.h>
#include "hcc.hpp"

// Test for hcc_encode
TEST(HccTest, EncodeTest) {
    // Mock test - just verify the function can be called
    EXPECT_NO_THROW(hcc::hcc_encode());
}

// Test for hcc_decode
TEST(HccTest, DecodeTest) {
    // Mock test - just verify the function can be called
    EXPECT_NO_THROW(hcc::hcc_decode());
}

// Test for hcc_32bit_encode
TEST(HccTest, Encode32BitTest) {
    uint32_t input = 0;
    char output[9] = {0};
    hcc::hcc_32bit_encode(input, output);
    EXPECT_EQ(output[0], hcc::HHC_ALPHABET[0]);
    EXPECT_EQ(output[1], hcc::HHC_ALPHABET[0]);
    EXPECT_EQ(output[2], hcc::HHC_ALPHABET[0]);
    EXPECT_EQ(output[3], hcc::HHC_ALPHABET[0]);
    EXPECT_EQ(output[4], hcc::HHC_ALPHABET[0]);
    EXPECT_EQ(output[5], hcc::HHC_ALPHABET[0]);
    EXPECT_EQ(output[6], hcc::HHC_ALPHABET[0]);
    EXPECT_EQ(output[7], hcc::HHC_ALPHABET[0]);
    EXPECT_EQ(output[8], hcc::HHC_ALPHABET[0]);
}

// Test for hcc_32bit_decode
TEST(HccTest, Decode32BitTest) {
    // Mock test - just verify the function can be called
    EXPECT_NO_THROW(hcc::hcc_32bit_decode());
}

// Test for hcc_64bit_encode
TEST(HccTest, Encode64BitTest) {
    // Mock test - just verify the function can be called
    EXPECT_NO_THROW(hcc::hcc_64bit_encode());
}

// Test for hcc_64bit_decode
TEST(HccTest, Decode64BitTest) {
    // Mock test - just verify the function can be called
    EXPECT_NO_THROW(hcc::hcc_64bit_decode());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
