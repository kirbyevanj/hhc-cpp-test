# GitHub Actions Workflows

This directory contains CI/CD workflows for the HHC C++ library.

## Workflows

### 1. CI (`ci.yml`)
**Triggers:** Push to main/develop, Pull Requests

Comprehensive continuous integration workflow that:
- **Builds and tests** on multiple platforms (Ubuntu, macOS) and architectures (AMD64, ARM64)
- **Runs linting** with clang-tidy
- **Executes benchmarks** on both architectures
- **Generates code coverage** reports and uploads to Codecov
- **Runs C++ examples** to verify functionality

**Matrix:**
- OS: Ubuntu (latest), macOS (latest)
- Architecture: AMD64, ARM64
- Compiler: Clang

### 2. Python Package (`python.yml`)
**Triggers:** Push to main/develop, Pull Requests, Tags (v*)

Python package building and distribution workflow that:
- **Builds wheels** for multiple Python versions (3.8-3.12) using cibuildwheel
- **Supports multiple platforms**: Linux (AMD64, ARM64), macOS (AMD64, ARM64), Windows (AMD64)
- **Builds source distribution** (sdist)
- **Tests Python package** on all platforms
- **Publishes to PyPI** on version tags (v*)
- **Publishes to Test PyPI** on develop branch pushes

**Python Versions:** 3.8, 3.9, 3.10, 3.11, 3.12

### 3. Fuzzing (`fuzzing.yml`)
**Triggers:** Push to main/develop, Pull Requests, Daily schedule (2 AM UTC)

Fuzzing workflow using LibFuzzer that:
- **Builds fuzzing targets** (decode32, decode64)
- **Runs fuzzers** for a short duration in CI
- **Uploads fuzzing corpus** as artifacts
- **Verifies OSS-Fuzz compatibility**

### 4. Release (`release.yml`)
**Triggers:** Version tags (v*)

Release workflow that:
- **Creates GitHub releases** with auto-generated changelogs
- **Builds release artifacts** for multiple platforms and architectures
- **Packages binaries** as tar.gz archives
- **Uploads artifacts** to GitHub releases

**Platforms:** Linux (AMD64, ARM64), macOS (AMD64, ARM64)

### 5. Documentation (`docs.yml`)
**Triggers:** Push to main

Documentation generation and deployment workflow that:
- **Generates API documentation** using Doxygen
- **Deploys to GitHub Pages** automatically
- **Includes call graphs** and dependency diagrams

## Required Secrets

### For PyPI Publishing
- `CODECOV_TOKEN` (optional): For uploading coverage reports to Codecov
- `TEST_PYPI_API_TOKEN` (optional): For publishing to Test PyPI

### For PyPI Trusted Publishing
Configure trusted publishing in your PyPI project settings:
1. Go to PyPI project settings
2. Add a new "trusted publisher"
3. Set workflow name: `python.yml`
4. Set environment name: `pypi`

## Architecture Support

All workflows support both AMD64 and ARM64 architectures:

- **AMD64 (x86_64)**: Native execution on GitHub-hosted runners
- **ARM64 (aarch64)**: 
  - Linux: Uses QEMU with `uraimo/run-on-arch-action`
  - macOS: Native execution on Apple Silicon runners (when available)

## Local Testing

### Test C++ builds locally:
```bash
# AMD64
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure

# With coverage
cmake -B build -DHHC_ENABLE_COVERAGE=ON
cmake --build build --target coverage
```

### Test Python builds locally:
```bash
cd python
pip install -e .
python test_hhc.py -v
```

### Test with cibuildwheel:
```bash
pip install cibuildwheel
cd python
cibuildwheel --platform linux
```

## Workflow Status Badges

Add these to your README.md:

```markdown
[![CI](https://github.com/kirbyevanj/hhc-cpp/actions/workflows/ci.yml/badge.svg)](https://github.com/kirbyevanj/hhc-cpp/actions/workflows/ci.yml)
[![Python Package](https://github.com/kirbyevanj/hhc-cpp/actions/workflows/python.yml/badge.svg)](https://github.com/kirbyevanj/hhc-cpp/actions/workflows/python.yml)
[![codecov](https://codecov.io/gh/kirbyevanj/hhc-cpp/branch/main/graph/badge.svg)](https://codecov.io/gh/kirbyevanj/hhc-cpp)
```

## Performance Considerations

- **Caching**: Dependencies are cached where possible to speed up builds
- **Parallel builds**: All builds use `--parallel` flag
- **Matrix strategy**: Jobs run in parallel across different configurations
- **Fail-fast disabled**: Allows all configurations to complete even if one fails

## Troubleshooting

### ARM64 builds are slow
ARM64 builds on Linux use QEMU emulation, which is slower than native execution. This is expected.

### Python wheel build fails
- Check that C++23 is properly supported
- Verify pybind11 version compatibility
- Check cibuildwheel logs for detailed error messages

### Coverage upload fails
- Ensure `CODECOV_TOKEN` is set in repository secrets
- Check that coverage files are generated correctly
- Verify Codecov integration is enabled for the repository

