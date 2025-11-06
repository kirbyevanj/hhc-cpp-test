#include <gtest/gtest.h>
#include "hhc.hpp"
#include <string>

// Test for hhc_32bit_encode
TEST(HhcTest, Encode32BitTest0) {
    char output[9] = {0};
    hhc::hhc_32bit_encode(0, output);
    EXPECT_STREQ(output, "--------");
}

TEST(HhcTest, Encode32BitTest1) {
    char output[9] = {0};
    hhc::hhc_32bit_encode(1, output);
    EXPECT_STREQ(output, "-------.");
}

// Test for hhc_32bit_decode
TEST(HhcTest, Decode32BitTest0) {
    std::string input = "--------";
    uint32_t output = hhc::hhc_32bit_decode(input.c_str());
    EXPECT_EQ(output, 0);
}

TEST(HhcTest, Decode32BitTest1) {
    std::string input = "-------.";
    uint32_t output = hhc::hhc_32bit_decode(input.c_str());
    EXPECT_EQ(output, 1);
}

TEST(HhcTest, RoundTrip32BitTestZeroTo1Million) {
    for (uint32_t i = 0; i < 1000000; i++) {
        char output[9] = {0};
        hhc::hhc_32bit_encode(i, output);
        uint32_t decoded = hhc::hhc_32bit_decode(output);
        ASSERT_EQ(decoded, i);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
