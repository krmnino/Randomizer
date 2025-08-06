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
3. Issue the command `make`. This will place the library file in `../res/libRandomizer.hpp`.
4. You may now copy the header file `Randomizer.hpp` and `../res/libRandomizer.hpp` to your own project. Check the Makefile in `../testing` for a usage example.

## Changelog

### v1.1

- Removed word `random` from generation method names.
- Update method names for creating and ending Randomizer instances.
- Updated `gen_string` generate an output string restricted to characters present in a `std::string` dictionary argument.
- Added variation of `gen_string` to allow dictionary to be of type `const char*`.
- Added `gen_bool` method.

### v1.0

- Initial release.
