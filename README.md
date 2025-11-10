# Randomizer

A small pseudo-random number generation library for reproducible execution paths in C/C++.

## Repository Structure

- `src`: contains all the source files, Makefile, and bash script required to build the `libRandomizer.so` file.
- `testing`: contains usage examples of the Randomizer library.

## Requirements and Dependencies

- C++17
- Make

## Build

1. Navigate into `src`.
2. Issue the command `sh Initialize.sh` to prepare the environment before creating the library file.
3. Issue the command `make`. This will generate and place the library file in `res/libRandomizer.so`.
4. You can now copy the shared object file `res/libRandomizer.so` to a desired location for your project.
5. If you intend to integrate `Randomizer` to a C++ project, you should copy the header file `src/Randomizer.hpp` to a desired location for your project.
6. If you intend to integrate `Randomizer` to a C project, you should copy the header file `src/Randomizer_C.h` to a desired location for your project.

## Usage for C++ Integration

### `Randomizer()`

- **Input arguments**: none
- **Output**: a `Randomizer` instance.
- Default constructor method that sets the `Randomizer`'s root seed to the value of 1. The MINSTD algorithm is applied to the root seed once to generate the branching seed.

### `Randomizer(uint32_t input_seed)`

- **Input arguments**:
  - `input_seed`: the initial root seed value.
- **Output**: a `Randomizer` instance.
- A constructor method that takes an initial seed value that is set to `Randomizer`'s root seed. The MINSTD algorithm is applied to the root seed once to generate the branching seed.

### `void root_seed_next()`

- **Input arguments**: none
- **Output**: none
- This method applies the MINSTD algorithm to the current root seed to generate the next root seed value.

### `void root_seed_prev()`

- **Input arguments**: none
- **Output**: none
- This method applies the inverse MINSTD algorithm to the current root seed to generate the previous root seed value.

### `uint32_t get_root_seed()`

- **Input arguments**: none
- **Output**: current root seed value.

### `uint32_t get_branching_seed()`

- **Input arguments**:
- **Output**: current branching seed value.
- The branching seed value is updated every time by applying the MINSTD algorithm when any of the generator methods are invoked.

### `bool gen_bool()`

- **Input arguments**: none
- **Output**: a pseudo-random boolean value.
- This generator method returns a pseudo-random boolean value.

### `std::string gen_string(size_t out_str_length, const char* dictionary)`

- **Input arguments**:
  - `size_t out_str_length`: the length of the string in number of characters to be generated.
  - `const char* dictionary`: source string to pick characters from.
- **Output**: the output string of length `out_str_length`.
- If the input argument is `dictionary` is `nullptr`, the method will the following default source: `!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_``abcdefghijklmnopqrstuvwxyz{|}~`

### `std::string gen_string(size_t out_str_length, std::string& dictionary)`

- **Input arguments**:
  - `size_t out_str_length`: the length of the string in number of characters to be generated.
  - `std::string& dictionary`: reference to a source string to pick characters from.
- **Output**: the output string of length `out_str_length`.
- This is method calls `std::string gen_string(size_t out_str_length, const char* dictionary)` to generate the pseudo-random string of length `out_str_length`.

### `double gen_double_not_nan()`

- **Input arguments**: none
- **Output**: the output floating-point value.
- This method allows specifying the data type for the return integer value.

### `double gen_double_not_nan_range(double lower, double upper)`

- **Input arguments**:
  - `lower`: lower boundary for the range to generate floating-point value.
  - `upper`: upper boundary for the range to generate floating-point value.
- **Output**: the output floating-point value.
- This method returns a pseudo-random floating-point value within the desired range.

### `template<typename T> T gen_integral()`

- **Input arguments**: none
- **Output**: the output integer value.
- This method allows specifying the data type for the return integer value.

### `template<typename T> T gen_integral_range(T lower, T upper)`

- **Input arguments**:
  - `lower`: lower boundary for the range to generate integer value.
  - `upper`: upper boundary for the range to generate integer value.
- **Output**: the output integer value.
- This method allows specifying the data type for the lower range, upper range, and return integer values.

### `template<typename T> int shuffle(T* array, size_t n_elements)`

- **Input arguments**:
  - `array`: a pointer to an array of elements of type `T`.
  - `n_elements`: number of elements in the array.
- **Output**: The method returns 0 if the shuffle operation was successful. Otherwise, a value of -1 is returned if the `T* array` argument is `nullptr` or `size_t n_elements` is 0.
- This method performs the Fisher-Yates shuffling algorithm in place over an array of elements of type `T`.

## Usage for C Integration

### `Randomizer_C* Randomizer_C_init(uint32_t input_seed)`

- **Input arguments**:
  - `input_seed`: the initial root seed value.
- **Output**: a pointer to `Randomizer_C` object.
- This function calls the `Randomizer` constructor method `Randomizer(uint32_t input_seed)`.

### `int Randomizer_C_delete(Randomizer_C* rndc)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
- **Output**: returns 0 if the delete operation was successful. Returns -1 if `rndc` is `NULL`.
- This method calls the `Randomizer`'s destructor method.

### `void Randomizer_C_root_seed_next(Randomizer_C* rndc)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
- **Output**: none
- This function calls the `Randomizer` method `void root_seed_next()`.

### `void Randomizer_C_root_seed_prev(Randomizer_C* rndc)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
- **Output**: none
- This function calls the `Randomizer` method `void root_seed_prev()`.

### `uint32_t Randomizer_C_get_root_seed(Randomizer_C* rndc)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
- **Output**: current root seed value.
- This function calls the `Randomizer` method `uint32_t get_root_seed()`.

### `uint32_t Randomizer_C_get_branching_seed(Randomizer_C* rndc)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
- **Output**: current branching seed value.
- This function calls the `Randomizer` method `uint32_t get_branching_seed()`.

### `bool Randomizer_C_gen_bool(Randomizer_C* rndc)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
- **Output**: a pseudo-random boolean value.
- This function calls the `Randomizer` method `bool gen_bool()`.

### `int Randomizer_C_gen_string(Randomizer_C* rndc, char* output_str, size_t out_str_length, const char* dictionary)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
  - `output_str`: a pointer to the buffer to be populated with pseudo-random string.
  - `size_t out_str_length`: the length of the string in number of characters to be generated.
  - `const char* dictionary`: source string to pick characters from.
- **Output**: return 0 if successful generating a pseudo-random string given the arguments provided. Return -1 if `output_str` is a `NULL` pointer.
- This function calls the `Randomizer` method `std::string gen_string(size_t out_str_length, const char* dictionary)`.

### `double Randomizer_C_gen_double_not_nan(Randomizer_C* rndc)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
- **Output**: the output floating-point value.
- This function calls the `Randomizer` method `double gen_double_not_nan()`.

### `double Randomizer_C_gen_double_not_nan_range(Randomizer_C* rndc, double lower, double upper)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
  - `lower`: lower boundary for the range to generate floating-point value.
  - `upper`: upper boundary for the range to generate floating-point value.
- **Output**: the output floating-point value.
- This function calls the `Randomizer` method `double gen_double_not_nan_range(double lower, double upper)`.

### `uint64_t Randomizer_C_gen_integral(Randomizer_C* rndc)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
- **Output**: the output integer value.
- This function calls the `Randomizer` method `template<typename T> T gen_integral()`.
- The returned value is a data type `uint64_t`.

### `uint64_t Randomizer_C_gen_integral_range(Randomizer_C* rndc, uint64_t lower, uint64_t upper)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
  - `lower`: lower boundary for the range to generate integer value.
  - `upper`: upper boundary for the range to generate integer value.
- **Output**: the output integer value.
- This function calls the `Randomizer` method `template<typename T> T gen_integral_range(T lower, T upper)`.
- The returned value is a data type `uint64_t`.

### `int Randomizer_C_shuffle(Randomizer_C* rndc, void* array, size_t n_elements, size_t elem_size)`

- **Input arguments**:
  - `rndc`: a pointer to a `Randomizer_C*` object.
  - `array`: a pointer to an array of elements.
  - `n_elements`: number of elements in the array.
- **Output**: The function returns 0 if the shuffle operation was successful. Otherwise, a value of -1 is returned if the `T* array` argument is `nullptr` or `size_t n_elements` is 0.
- This function implements the Fisher-Yates shuffling algorithm and does not call the `Randomizer` C++ shuffle method to perform this operation.

## Changelog

### v1.4

- Removed singleton implementation for `Randomizer` class allowing multiple instances to be created in a program.
- Renaming `testing/Main.cpp` to `testing/RandomizerExample.cpp`.
- Updates to `testing/RandomizerExample.cpp` reflecting changes to removal of singleton implementation.
- Definition of API for integration with C projects, including the following functions:
  - `Randomizer_C* Randomizer_C_init(uint32_t)`
  - `int Randomizer_C_delete(Randomizer_C*)`
  - `void Randomizer_C_root_seed_next(Randomizer_C*)`
  - `void Randomizer_C_root_seed_prev(Randomizer_C*)`
  - `uint32_t Randomizer_C_get_root_seed(Randomizer_C*)`
  - `uint32_t Randomizer_C_get_branching_seed(Randomizer_C*)`
  - `bool Randomizer_C_gen_bool(Randomizer_C*)`
  - `int Randomizer_C_gen_string(Randomizer_C*, char*, size_t, const char*)`
  - `double Randomizer_C_gen_double_not_nan(Randomizer_C*)`
  - `double Randomizer_C_gen_double_not_nan_range(Randomizer_C*, double, double)`
  - `uint64_t Randomizer_C_gen_integral(Randomizer_C*)`
  - `uint64_t Randomizer_C_gen_integral_range(Randomizer_C*, uint64_t, uint64_t)`
  - `int Randomizer_C_shuffle(Randomizer_C*, void*, size_t, size_t)`
- Miscellaneous fixes and code clean up.

### v1.3

- `shuffle(T, size_t)` does not need to know element size.
- Use `std::swap` in `shuffle(T, size_t)` for swapping elements in array.

### v1.2

- Added method `get_root_seed()`.
- Added method `get_branching_seed()`.
- Added method `shuffle(void*, size_t, size_t)` that implements variation of the Fisher-Yates shuffling algorithm.
- Added wrapper method `shuffle(std::vector<T>&)` that accepts an `std::vector` and invokes `shuffle(void*, size_t, size_t)`.

### v1.1

- Removed word `random` from generation method names.
- Update method names for creating and ending Randomizer instances.
- Updated `gen_string(size_t, std::string&);` generate an output string restricted to characters present in a `std::string` dictionary argument.
- Added variation of `gen_string(size_t, const char*);` to allow dictionary to be of type `const char*`.
- Added `gen_bool()` method.

### v1.0

- Initial release.
