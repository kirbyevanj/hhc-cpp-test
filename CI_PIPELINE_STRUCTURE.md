# CI Pipeline Structure

## Overview

The CI pipeline is organized into 4 stages with parallel execution in Stage 4.

## Pipeline Flow

```
┌─────────────────────────────────────────────────────────────────┐
│                          STAGE 1: LINT                          │
│                     (clang-tidy on all files)                   │
│                         Must pass to continue                    │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│                    STAGE 2: BUILD & TEST                        │
│                                                                 │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐        │
│  │ Ubuntu AMD64 │  │ Ubuntu ARM64 │  │ macOS AMD64  │        │
│  └──────────────┘  └──────────────┘  └──────────────┘        │
│  ┌──────────────┐                                              │
│  │ macOS ARM64  │                                              │
│  └──────────────┘                                              │
│                                                                 │
│  All platforms: Build → Test → Run Examples                    │
│  fail-fast: true (stop on first failure)                       │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│                     STAGE 3: BENCHMARKS                         │
│                                                                 │
│  ┌──────────────┐  ┌──────────────┐                           │
│  │ Ubuntu AMD64 │  │ Ubuntu ARM64 │                           │
│  └──────────────┘  └──────────────┘                           │
│                                                                 │
│  Run performance benchmarks                                     │
└────────────────────────────┬────────────────────────────────────┘
                             │
                             ▼
┌─────────────────────────────────────────────────────────────────┐
│                   STAGE 4: PARALLEL EXECUTION                   │
│                                                                 │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │ 4a: Code Coverage                                        │  │
│  │     - Generate coverage report                           │  │
│  │     - Upload to Codecov                                  │  │
│  └──────────────────────────────────────────────────────────┘  │
│                                                                 │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │ 4b: Python Wheels                                        │  │
│  │     - Build wheels (Ubuntu/macOS/Windows, AMD64/ARM64)   │  │
│  │     - Build sdist                                        │  │
│  └─────────────────────┬────────────────────────────────────┘  │
│                        │                                        │
│                        ▼                                        │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │ 4c: Test Python                                          │  │
│  │     - Test wheels on all platforms                       │  │
│  │     - Run Python tests                                   │  │
│  │     - Run Python examples                                │  │
│  └─────────────────────┬────────────────────────────────────┘  │
│                        │                                        │
│                        ▼                                        │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │ 4d: Publish to PyPI (conditional)                        │  │
│  │     - Publish to PyPI (if: tag v*)                       │  │
│  │     - Publish to Test PyPI (if: branch develop)          │  │
│  │     - Skipped otherwise (does NOT fail pipeline)         │  │
│  └──────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
```

## Stage Details

### Stage 1: Lint
- **Runs on**: `ubuntu-latest`
- **Duration**: ~2 minutes
- **Behavior**: Must pass for pipeline to continue
- **Actions**: Run clang-tidy on all source files

### Stage 2: Build & Test
- **Runs on**: 
  - Ubuntu AMD64 (`ubuntu-latest`)
  - Ubuntu ARM64 (`ubuntu-24.04-arm`)
  - macOS AMD64 (`macos-13`)
  - macOS ARM64 (`macos-14`)
- **Duration**: ~5-7 minutes per platform
- **Behavior**: `fail-fast: true` - stops on first failure
- **Actions**:
  1. Build C++ library
  2. Run unit tests
  3. Run C++ examples

### Stage 3: Benchmarks
- **Runs on**:
  - Ubuntu AMD64 (`ubuntu-latest`)
  - Ubuntu ARM64 (`ubuntu-24.04-arm`)
- **Duration**: ~3-5 minutes per platform
- **Behavior**: `fail-fast: false` - both platforms complete
- **Actions**: Run performance benchmarks

### Stage 4: Parallel Execution

All Stage 4 jobs run in parallel after benchmarks complete.

#### 4a: Code Coverage
- **Runs on**: `ubuntu-latest`
- **Duration**: ~4 minutes
- **Behavior**: Always runs (no conditions)
- **Actions**:
  1. Build with coverage instrumentation
  2. Run tests with coverage
  3. Generate coverage report
  4. Upload to Codecov

#### 4b: Python Wheels
- **Runs on**: Multiple platforms (5 runners)
  - Ubuntu AMD64, Ubuntu ARM64
  - macOS AMD64, macOS ARM64
  - Windows AMD64
- **Duration**: ~5-10 minutes per platform
- **Behavior**: `fail-fast: false` - all platforms complete
- **Actions**: Build Python wheels using cibuildwheel

#### 4c: Test Python
- **Runs on**: Same 5 platforms as wheel building
- **Duration**: ~2-3 minutes per platform
- **Behavior**: `fail-fast: false` - all platforms complete
- **Actions**:
  1. Install built wheel
  2. Run Python unit tests
  3. Run Python examples

#### 4d: Publish to PyPI
- **Runs on**: `ubuntu-latest`
- **Duration**: ~1 minute
- **Behavior**: Conditional - skipped if conditions not met
- **Conditions**:
  - **PyPI**: Only on tags matching `v*`
  - **Test PyPI**: Only on `develop` branch
  - **Skipped**: All other cases (does NOT fail pipeline)
- **Actions**: Publish wheels and sdist to PyPI/Test PyPI

## Skipped Jobs Behavior

Jobs with `if` conditions that evaluate to `false` are marked as **"skipped"** (not failed):

```yaml
if: github.event_name == 'push' && startsWith(github.ref, 'refs/tags/v')
```

**Result:**
- ✅ **On tag push**: Job runs and publishes
- ⏭️ **On other events**: Job is skipped (shown in gray in GitHub UI)
- ✅ **Pipeline**: Continues successfully (skipped ≠ failed)

This means:
- Regular PRs and pushes complete successfully even though PyPI jobs are skipped
- Only version tags trigger PyPI publishing
- Only develop branch triggers Test PyPI publishing
- The pipeline never fails due to skipped publishing jobs

## Execution Times

### Fast Path (PR without publishing)
```
Lint:          ~2 min
Build & Test:  ~7 min (parallel across 4 platforms)
Benchmarks:    ~5 min (parallel across 2 platforms)
Coverage:      ~4 min (parallel with Python)
Python:        ~10 min (build + test, parallel)
Publishing:    skipped

Total: ~15-20 minutes
```

### Full Path (Version tag with publishing)
```
Lint:          ~2 min
Build & Test:  ~7 min
Benchmarks:    ~5 min
Coverage:      ~4 min (parallel)
Python:        ~10 min (parallel)
Publishing:    ~1 min

Total: ~15-20 minutes (publishing adds minimal time)
```

## Failure Scenarios

### Lint Fails
- Pipeline stops immediately
- No builds run
- Fast feedback (~2 min)

### Build Fails
- Pipeline stops after Stage 2
- No benchmarks run
- No coverage or Python builds
- Fast feedback (~7-9 min)

### Benchmark Fails
- Pipeline stops after Stage 3
- No coverage or Python builds
- Feedback in ~12-14 min

### Coverage Fails
- Python builds continue (parallel)
- Publishing continues (if applicable)
- Pipeline marked as failed but completes

### Python Build/Test Fails
- Coverage continues (parallel)
- Publishing is skipped (depends on Python tests)
- Pipeline marked as failed but completes

### Publishing Fails
- Only affects that specific job
- Other jobs already completed
- Easy to retry just the publishing step

## Benefits of This Structure

1. **Fast Feedback**: Lint runs first, fails fast
2. **Efficient Resource Use**: Parallel execution in Stage 4
3. **No False Failures**: Skipped jobs don't fail pipeline
4. **Easy Debugging**: Clear stage separation
5. **Flexible Publishing**: Conditional based on branch/tag
6. **Cost Effective**: Stops early on failures

## Monitoring

View pipeline status:
- GitHub Actions tab shows all stages
- Skipped jobs appear in gray
- Failed jobs appear in red
- Successful jobs appear in green
- Parallel jobs show side-by-side

