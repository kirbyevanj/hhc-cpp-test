#include <benchmark/benchmark.h>
#include "hhc.hpp"

// Benchmark for hhc_32bit_encode
static void BM_hhc32BitEncode(benchmark::State& state) {
    for (auto _ : state) {
        const uint32_t input = rand();

        char output[9] = {0};
        hhc::hhc_32bit_encode(input, output);

        benchmark::DoNotOptimize(output);
    }
}
BENCHMARK(BM_hhc32BitEncode);

// Benchmark for hhc_32bit_decode
static void BM_hhc32BitDecode(benchmark::State& state) {
    //state.PauseTiming();
    // Create block of 1024 characters from hhc::HHC_ALPHABET
    std::string input;
    input.resize(2048);
    for (int i = 0; i < 2048; i++) {
        input[i] = hhc::HHC_ALPHABET[rand() % BASE];
    }
    //state.ResumeTiming();
    for (auto _ : state) {
        // Get random index from input
        const uint32_t index = rand() % (input.length() - 8);
        uint32_t output = hhc::hhc_32bit_decode(input.c_str() + index);
        benchmark::DoNotOptimize(output);
    }
}
BENCHMARK(BM_hhc32BitDecode);

BENCHMARK_MAIN();
