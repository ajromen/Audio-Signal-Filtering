
# Audio Signal Filtering

Small C++ framework for filtering discrete signal samples with WAV output.

## Requirements

### Compiler

* **C++20 compatible compiler**

If your compiler doesn’t support C++20, this project will **not** build.

### Build system

* **CMake ≥ 4.0.1**

### Dependencies

* **CLI11** (command-line argument parser)

If you cloned this project install the dependencies running:
```bash
git update submodule --init --recursive
```

If `external/CLI11/include` is missing, the build will fail.


---

## Building the Project

### 1. Configure

From the project root:

```bash
cmake -S . -B build
```

### 2. Build

```bash
cmake --build build
```

### 3. Run

```bash
./build/Audio_Signal_Filtering
```
To see all options run with flag --help.

(On Windows: `build\Debug\Audio_Signal_Filtering.exe` or similar.)

---

## Enabling Test Mode

Tests are **internal** and compiled conditionally.

To build with tests enabled:

```bash
cmake -S . -B build -DTEST_MODE=ON
cmake --build build
```

The test logic lives in `src/tests.cpp`

There is **no external testing framework**.

