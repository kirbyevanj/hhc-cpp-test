# HHC Python Bindings

Python bindings for the HHC (High-performance Hash Codec) C++ library.

## Installation

### Method 1: Using CMake (recommended for development)

```bash
# From the root directory
mkdir build && cd build
cmake .. -DHHC_BUILD_PYTHON=ON
make

# The Python module will be in build/python/
```

### Method 2: Using setuptools

```bash
# From the python directory
cd python
pip install .

# Or for development
pip install -e .
```

## Requirements

- Python 3.6+
- pybind11
- C++23 compatible compiler (clang++ recommended)

## Usage

### Basic Example

```python
import hhc

# Encode a 32-bit value
value = 424242
padded = hhc.encode_padded_32bit(value)      # Returns: "--.TNv"
unpadded = hhc.encode_unpadded_32bit(value)  # Returns: ".TNv"

# Decode a string
decoded = hhc.decode_32bit(".TNv")  # Returns: 424242

# 64-bit operations
big_value = 9876543210
padded64 = hhc.encode_padded_64bit(big_value)      # Returns: "-----5tVfK4"
unpadded64 = hhc.encode_unpadded_64bit(big_value)  # Returns: "5tVfK4"
decoded64 = hhc.decode_64bit("5tVfK4")  # Returns: 9876543210
```

### Error Handling

```python
import hhc

try:
    # Invalid characters
    hhc.decode_32bit("INVALID!")
except ValueError as e:
    print(f"Invalid string: {e}")

try:
    # Value exceeds bounds
    hhc.decode_32bit("1QLCp2")  # Exceeds UINT32_MAX
except OverflowError as e:
    print(f"Value too large: {e}")
```

## API Reference

### Functions

- `encode_padded_32bit(value: int) -> str`: Encode a 32-bit integer to a padded 6-character string
- `encode_unpadded_32bit(value: int) -> str`: Encode a 32-bit integer to an unpadded string
- `decode_32bit(encoded: str) -> int`: Decode a string to a 32-bit integer
- `encode_padded_64bit(value: int) -> str`: Encode a 64-bit integer to a padded 11-character string
- `encode_unpadded_64bit(value: int) -> str`: Encode a 64-bit integer to an unpadded string
- `decode_64bit(encoded: str) -> int`: Decode a string to a 64-bit integer

### Constants

- `HHC_32BIT_ENCODED_LENGTH`: Length of padded 32-bit encoded strings (6)
- `HHC_64BIT_ENCODED_LENGTH`: Length of padded 64-bit encoded strings (11)
- `ALPHABET`: The HHC alphabet string

### Exceptions

- `ValueError`: Raised when decoding a string with invalid characters
- `OverflowError`: Raised when decoding a string that exceeds the bit bounds

## Examples

See the `examples/` directory for complete examples:
- `encode_example.py`: Demonstrates encoding functionality
- `decode_example.py`: Demonstrates decoding with error handling and round-trip tests
