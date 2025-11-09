# Contributing to HHC C++

Thank you for your interest in contributing to HHC C++! This document provides guidelines and instructions for contributing.

## Code of Conduct

Please be respectful and constructive in all interactions with the project.

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/kirbyevanj/hhc-cpp.git`
3. Create a feature branch: `git checkout -b feature/your-feature-name`
4. Make your changes
5. Run tests and ensure they pass
6. Commit your changes with clear commit messages
7. Push to your fork: `git push origin feature/your-feature-name`
8. Open a Pull Request

## Development Setup

### C++ Development

```bash
# Install dependencies (Ubuntu)
sudo apt-get install clang cmake ninja-build

# Build the project
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel

# Run tests
cd build && ctest --output-on-failure

# Run with coverage
cmake -B build -DHHC_ENABLE_COVERAGE=ON
cmake --build build --target coverage
```

### Python Development

```bash
# Install in development mode
cd python
pip install -e .

# Run tests
python test_hhc.py -v

# Run examples
python examples/encode_example.py
python examples/decode_example.py
```

## Code Style

### C++

- Follow C++23 standards
- Use `constexpr` where possible
- Prefer `std::ranges` and modern C++ features
- Use meaningful variable and function names
- Add documentation comments for public APIs
- Keep functions focused and small

### Python

- Follow PEP 8 style guide
- Use type hints where appropriate
- Write docstrings for all public functions
- Keep code simple and readable

## Testing

### C++ Tests

- Add unit tests for all new functionality in the `tests/` directory
- Use Google Test framework
- Ensure tests cover edge cases
- Run tests on both AMD64 and ARM64 if possible

### Python Tests

- Add tests to `python/test_hhc.py`
- Test both success and error cases
- Verify exception handling

## Benchmarking

- Add benchmarks for performance-critical code in `benchmarks/`
- Use Google Benchmark framework
- Document any performance improvements in PR description

## Documentation

- Update README.md if adding new features
- Add code comments for complex logic
- Update Python docstrings
- Update examples if API changes

## Commit Messages

Use clear, descriptive commit messages:

```
<type>: <subject>

<body>

<footer>
```

Types:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes (formatting, etc.)
- `refactor`: Code refactoring
- `test`: Adding or updating tests
- `perf`: Performance improvements
- `ci`: CI/CD changes
- `build`: Build system changes

Example:
```
feat: add support for unpadded encoding

Implement hhc_32bit_encode_unpadded and hhc_64bit_encode_unpadded
functions that produce variable-length encoded strings without
leading padding characters.

Closes #123
```

## Pull Request Process

1. Ensure all tests pass locally
2. Update documentation as needed
3. Add tests for new functionality
4. Fill out the PR template completely
5. Link related issues
6. Wait for CI checks to pass
7. Respond to review feedback promptly

## CI/CD Pipeline

All PRs must pass:
- Build on Ubuntu and macOS (AMD64 and ARM64)
- All unit tests
- Linting (clang-tidy)
- Benchmarks (should not significantly regress)
- Python tests (if applicable)

## Release Process

Releases are automated:
1. Update version in `CMakeLists.txt` and `python/setup.py`
2. Create a git tag: `git tag -a v1.0.0 -m "Release v1.0.0"`
3. Push the tag: `git push origin v1.0.0`
4. GitHub Actions will automatically:
   - Build release artifacts
   - Create GitHub release
   - Build and publish Python wheels to PyPI

## Questions?

- Open an issue for bugs or feature requests
- Check existing issues and PRs first
- Be patient and respectful

Thank you for contributing!

