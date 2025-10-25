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
3. Issue the command `make`. This will generate and place the library file in `../res/libRandomizer.so`.
4. You may now copy the header file `Randomizer.hpp` and `../res/libRandomizer.so` to your own project.

## Usage for C++ Integration

### `static Randomizer& get_instance(uint32_t input_seed)`

- **Input**:
  - `input_seed`: the initial root seed value.
- **Output**: none
- Only one instance of the `Randomizer` class is allowed to exist throughout the execution of the program.

### `void root_seed_next()`

- **Input**: none
- **Output**: none
- This method applies the MINSTD algorithm to the current root seed to generate the next root seed value.

### `void root_seed_prev()`

- **Input**: none
- **Output**: none
- This method applies the inverse MINSTD algorithm to the current root seed to generate the previous root seed value.

### `uint32_t get_root_seed()`

- **Input**: none
- **Output**: current root seed value.
- Returns the current root seed value in the `Randomizer` object.

### `uint32_t get_branching_seed()`

- **Input**:
- **Output**:
- Returns the current branching seed value in the `Randomizer` object.
- The branching seed value is updated every time by applying the MINSTD algorithm when any of the generator methods are invoked.

### `bool gen_bool()`

- **Input**: none
- **Output**: a pseudo-random boolean value.
- This generator method returns a pseudo-random boolean value.

### `std::string gen_string(size_t out_str_length, const char* dictionary)`

- **Input**:
  - `size_t out_str_length`: the length of the string in number of characters to be generated.
  - `const char* dictionary`: source string to pick characters from.
- **Output**: the output string of length `out_str_length`.
- If the input argument is `dictionary` is `nullptr`, the method will the following default source: `!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_``abcdefghijklmnopqrstuvwxyz{|}~`

### `std::string gen_string(size_t out_str_length, std::string& dictionary)`

- **Input**:
  - `size_t out_str_length`: the length of the string in number of characters to be generated.
  - `std::string& dictionary`: reference to a source string to pick characters from.
- **Output**: the output string of length `out_str_length`.
- This is method calls `std::string gen_string(size_t out_str_length, const char* dictionary)` to generate the pseudo-random string of length `out_str_length`.

## Usage for C Integration

TODO

## Changelog

### v1.4

- Implemented Meyers' Singleton for `Randomizer` class.
- Renaming `testing/Main.cpp` to `testing/RandomizerExample.cpp`.
- Updates to `testing/RandomizerExample.cpp` reflecting changes to support Meyers' Singleton implementation.

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
