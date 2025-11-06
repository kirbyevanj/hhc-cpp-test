# hhc-cpp

A C++23 header-only library for HHC encoding/decoding operations.

## Project Structure

```
hhc-cpp/
├── hhc-cpp/           # Header-only library
│   └── hhc.hpp
├── tests/             # GoogleTest unit tests
│   ├── CMakeLists.txt
│   └── test_hhc.cpp
├── benchmarks/        # Google Benchmark performance tests
│   ├── CMakeLists.txt
│   └── benchmark_hhc.cpp
├── CMakeLists.txt     # Root CMake configuration
└── .gitignore
```

## Building the Project

### Prerequisites

- CMake 3.20 or higher
- C++23 compatible compiler (GCC 11+, Clang 15+, or MSVC 2022+)
- Git (for fetching GoogleTest and Google Benchmark)

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure the project (defaults to Release build)
cmake ..

# Or specify build type explicitly
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build all targets
cmake --build .
```

**Build Types:**
- `Release` (default) - Optimized for performance, recommended for benchmarks
- `Debug` - Include debug symbols, no optimizations
- `RelWithDebInfo` - Optimized with debug info
- `MinSizeRel` - Optimized for size

## Running Tests

```bash
# From the build directory
./tests/hhc_tests

# Or using CTest
ctest --output-on-failure
```

## Running Benchmarks

```bash
# From the build directory
./benchmarks/hhc_benchmarks
```

## Using the Library

The library is header-only, so simply include it in your project:

```cpp
#include "hhc.hpp"

int main() {
    hhc::hhc_encode();
    hhc::hhc_decode();
    hhc::hhc_32bit_encode();
    hhc::hhc_32bit_decode();
    hhc::hhc_64bit_encode();
    hhc::hhc_64bit_decode();
    return 0;
}
```

## API Reference

### Functions

- `void hhc_encode()` - Encode data using HHC algorithm
- `void hhc_decode()` - Decode HHC-encoded data
- `void hhc_32bit_encode()` - Encode data using 32-bit HHC variant
- `void hhc_32bit_decode()` - Decode 32-bit HHC-encoded data
- `void hhc_64bit_encode()` - Encode data using 64-bit HHC variant
- `void hhc_64bit_decode()` - Decode 64-bit HHC-encoded data

All functions are in the `hhc` namespace.

## External Dependencies

- [GoogleTest](https://github.com/google/googletest) - v1.14.0 (automatically downloaded)
- [Google Benchmark](https://github.com/google/benchmark) - v1.8.3 (automatically downloaded)

Dependencies are managed via CMake's ExternalProject_Add and will be automatically downloaded and built during configuration.

## IDE Setup (clangd)

The project includes a `.clangd` configuration file for accurate IntelliSense. For best results:

1. **Build the project** to generate `compile_commands.json`:
   ```bash
   mkdir build && cd build
   cmake ..
   ```

2. **Create a symlink** in the project root (optional but recommended):
   ```bash
   ln -s build/compile_commands.json compile_commands.json
   ```

3. **Restart your language server** - clangd will now have full understanding of your project

The `.clangd` config provides:
- C++23 standard support
- Proper include paths for the header-only library
- ClangTidy checks for code quality
- IntelliSense with parameter names and deduced types

## Notes

- Benchmarks use `benchmark::ClobberMemory()` to prevent compiler optimizations from eliminating the function calls
- The library functions are currently stubs (TODO) for demonstration purposes

