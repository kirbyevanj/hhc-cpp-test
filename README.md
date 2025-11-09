# hhc-cpp

A C++23 header-only library for HHC encoding/decoding operations.

## Project Structure

```
hhc-cpp/
├── hhc-cpp/           # Header-only library
│   ├── hhc.hpp
│   └── hhc_constants.hpp
├── tests/             # GoogleTest unit tests
├── benchmarks/        # Google Benchmark performance tests
├── examples/          # C++ usage examples
├── python/            # Python bindings (optional)
│   ├── hhc_python.cpp # pybind11 bindings
│   ├── setup.py       # Python package setup
│   └── examples/      # Python usage examples
├── fuzz/              # LibFuzzer tests (optional)
├── CMakeLists.txt     # Root CMake configuration
└── .gitignore
```

## Building the Project

### Prerequisites

- CMake 3.20 or higher
- C++23 compatible compiler (GCC 11+, Clang 15+, or MSVC 2022+)
- Git (for fetching GoogleTest and Google Benchmark)
- Python 3.6+ and pybind11 (optional, for Python bindings)

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

# Or build with Python bindings
cmake -DHHC_BUILD_PYTHON=ON ..
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

## API Reference


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

## Python Bindings

The library provides Python bindings through pybind11. To use:

### Building with CMake

```bash
mkdir build && cd build
cmake -DHHC_BUILD_PYTHON=ON ..
cmake --build .

# Test the module
PYTHONPATH=./python python3 -c "import hhc; print(hhc.encode_padded_32bit(42))"
```

### Building with setuptools

```bash
cd python
pip install .
```

### Python API

```python
import hhc

# 32-bit operations
encoded = hhc.encode_padded_32bit(424242)      # Returns: "--.TNv"
encoded = hhc.encode_unpadded_32bit(424242)    # Returns: ".TNv"
decoded = hhc.decode_32bit(".TNv")             # Returns: 424242

# 64-bit operations
encoded = hhc.encode_padded_64bit(9876543210)  # Returns: "-----5tVfK4"
encoded = hhc.encode_unpadded_64bit(9876543210) # Returns: "5tVfK4"
decoded = hhc.decode_64bit("5tVfK4")           # Returns: 9876543210
```

See `python/examples/` for more detailed examples.

