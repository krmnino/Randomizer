#ifndef RANDOMIZER_C
#define RANDOMIZER_C

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Randomizer_C Randomizer_C;

Randomizer_C* Randomizer_C_get_instance();
void Randomizer_C_root_seed_next(Randomizer_C*);
void Randomizer_C_root_seed_prev(Randomizer_C*);

#ifdef __cplusplus
}
#endif

#endif // ifndef RANDOMIZER_C