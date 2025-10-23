#ifndef RANDOMIZER_C
#define RANDOMIZER_C

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Randomizer_C Randomizer_C;

Randomizer_C* Randomizer_C_get_instance(uint32_t);
void Randomizer_C_root_seed_next(Randomizer_C*);
void Randomizer_C_root_seed_prev(Randomizer_C*);
bool Randomizer_C_gen_bool(Randomizer_C*);
uint64_t Randomizer_C_gen_integral(Randomizer_C*);
uint64_t Randomizer_C_gen_integral_range(Randomizer_C*, uint64_t, uint64_t);

#ifdef __cplusplus
}
#endif

#endif // ifndef RANDOMIZER_C