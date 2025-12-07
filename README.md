# Zenith

## 1. Development Environment

### Build Docker Image
```bash
docker build --network=host -t zenithbuilder:v6 -f devenv/Dockerfile devenv
```

### Run Container
```bash
docker run -it --name zenith -v $(pwd):/app/zenith zenithbuilder:v6 bash
```

## Build Instructions

We use **CMake Presets** to simplify building with different compilers and configurations. All builds are output to the `build/` directory.

### 1. Standard Builds

| Preset Name | Compiler | Build Type | Output Directory |
| :--- | :--- | :--- | :--- |
| `gcc-release` | GCC | Release | `build/gcc-release` |
| `gcc-debug` | GCC | Debug | `build/gcc-debug` |
| `clang-release` | Clang | Release | `build/clang-release` |
| `clang-debug` | Clang | Debug | `build/clang-debug` |

**Command:**
```bash
# Configure
cmake --preset <preset-name>

# Build (Recommended: Use half of available cores to avoid freezing)
cmake --build --preset <preset-name> -j2
```

### 2. Sanitizer Builds (Debug)

| Preset Name | Sanitizer | Compiler | Notes |
| :--- | :--- | :--- | :--- |
| `gcc-asan` | Address | GCC | **Recommended** for daily dev. |
| `clang-asan` | Address | Clang | Alternative ASan build. |
| `clang-tsan` | Thread | Clang | **Note**: May fail in Docker due to `personality` syscall restrictions. |
| `clang-msan` | Memory | Clang | **Experimental**. Requires instrumented libc++. |

**Example (GCC ASan):**
```bash
cmake --preset gcc-asan
cmake --build --preset gcc-asan -j2
```

## Clean Builds

We use **Ninja** as the build system (faster than Make, better dependency tracking).

### Incremental Clean (Daily Development)
Removes build artifacts but preserves CMake cache. Fast reconfigure-free rebuilds.
```bash
ninja -C build/gcc-debug clean
```

### Full Clean (CMake Changes, Troubleshooting)
Nuclear option - deletes everything. Requires full reconfigure.
```bash
rm -rf build/gcc-debug

# Or clean all presets
rm -rf build/
```

**Clean → Build workflow:**
```bash
# Incremental (fast)
ninja -C build/gcc-debug clean
ninja -C build/gcc-debug -j2

# Full rebuild
rm -rf build/gcc-debug
cmake --preset gcc-debug
cmake --build --preset gcc-debug -j2
```

## Testing

We use **GoogleTest** for all unit tests.

### Run All Tests
```bash
# Using CTest (Recommended)
ctest --preset gcc-debug

# Or using Ninja directly
cd build/gcc-debug && ninja test
```

### Run Specific Component Tests
You can run tests for a specific component (e.g., `router`, `http1.1server`) by targeting its GTest executable.

```bash
# Build and run just the router tests
cmake --build --preset gcc-debug --target router_gtest
./build/gcc-debug/router/tests/router_gtest
```

### Run Specific Test Cases
Use `--gtest_filter` to run specific test cases.

```bash
# Run only the ExactMatch test in Router
./build/gcc-debug/router/tests/router_gtest --gtest_filter=RouterTest.ExactMatch
```

## Verification (Valgrind)

We provide a unified target to run all Valgrind tools (MemCheck, Helgrind, Massif, Callgrind, Cachegrind).
**Note**: Valgrind targets are only available in **Debug** builds (e.g., `gcc-debug`).

### Run All Valgrind Checks
```bash
cmake --build --preset gcc-debug --target test_valgrind_all
```

### Run Specific Checks
```bash
cmake --build --preset gcc-debug --target test_memcheck   # Memory Leaks
cmake --build --preset gcc-debug --target test_helgrind   # Thread Safety
cmake --build --preset gcc-debug --target test_massif     # Heap Profiling
```

## Code Coverage

We support code coverage analysis for both **GCC** (using gcov/lcov) and **Clang** (using llvm-cov).
Coverage reports are generated as HTML for easy visualization.

### Coverage Presets

| Preset Name | Compiler | Coverage Tool | Output Directory |
| :--- | :--- | :--- | :--- |
| `gcc-coverage` | GCC | gcov + lcov | `build/gcc-coverage` |
| `clang-coverage` | Clang | llvm-cov | `build/clang-coverage` |

### Workflow

**1. Configure with coverage preset:**
```bash
cmake --preset gcc-coverage
# or
cmake --preset clang-coverage
```

**2. Build the project:**
```bash
cmake --build --preset gcc-coverage -j2
# or
cmake --build --preset clang-coverage -j2
```

**3. Run tests to generate coverage data:**
```bash
ctest --preset gcc-coverage
# or
ctest --preset clang-coverage
```

**4. Generate HTML coverage report:**
```bash
cmake --build --preset gcc-coverage --target coverage_report
# or
cmake --build --preset clang-coverage --target coverage_report
```

**5. View the report:**

If running in Docker, copy the coverage report to your local machine:
```bash
# From your local machine (outside Docker)
docker cp zenith:/app/zenith/build/gcc-coverage/coverage_html ./coverage_html
# or
docker cp zenith:/app/zenith/build/clang-coverage/coverage_html ./coverage_html
```

Then open `index.html` in your browser:
```bash
# On your local machine
open coverage_html/index.html  # macOS
xdg-open coverage_html/index.html  # Linux
start coverage_html/index.html  # Windows
```

Alternatively, if running natively (not in Docker):
```bash
xdg-open build/gcc-coverage/coverage_html/index.html
# or
xdg-open build/clang-coverage/coverage_html/index.html
```

### Clean Coverage Data

To reset coverage counters and remove reports:
```bash
cmake --build --preset gcc-coverage --target coverage_clean
# or
cmake --build --preset clang-coverage --target coverage_clean
```
