#ifndef RANDOMIZER_C
#define RANDOMIZER_C

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Randomizer_C Randomizer_C;

Randomizer_C* Randomizer_C_init(uint32_t);
int Randomizer_C_delete(Randomizer_C*);
void Randomizer_C_root_seed_next(Randomizer_C*);
void Randomizer_C_root_seed_prev(Randomizer_C*);
uint32_t Randomizer_C_get_root_seed(Randomizer_C*);
uint32_t Randomizer_C_get_branching_seed(Randomizer_C*);
bool Randomizer_C_gen_bool(Randomizer_C*);
int Randomizer_C_gen_string(Randomizer_C*, char*, size_t, const char*);
double Randomizer_C_gen_double(Randomizer_C*);
double Randomizer_C_gen_double_not_nan_range(Randomizer_C*, double, double);
uint64_t Randomizer_C_gen_integral(Randomizer_C*);
uint64_t Randomizer_C_gen_integral_range(Randomizer_C*, uint64_t, uint64_t);
int Randomizer_C_shuffle(Randomizer_C*, void*, size_t, size_t);

#ifdef __cplusplus
}
#endif

#endif // ifndef RANDOMIZER_C