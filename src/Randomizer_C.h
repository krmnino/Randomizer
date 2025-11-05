#ifndef RANDOMIZER_C
#define RANDOMIZER_C

#include <stdbool.h>
#include <stdint.h>
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
double Randomizer_C_gen_double_not_nan(Randomizer_C*);
double Randomizer_C_gen_double_not_nan_range(Randomizer_C*, double, double);
uint64_t Randomizer_C_gen_integral(Randomizer_C*);
uint64_t Randomizer_C_gen_integral_range(Randomizer_C*, uint64_t, uint64_t);

int Randomizer_C_shuffle(Randomizer_C* rndc, void* array, size_t n_elements, size_t elem_size){
    size_t rand_idx;
    // Check for zeros or NULL
    if(array == NULL || n_elements == 0 || elem_size == 0){
        return -1;
    }
    // Nothing to shuffle
    if(n_elements == 1){
        return 0;
    }
    uint8_t* buff;
    buff = (uint8_t*)calloc(1, elem_size);
    // Variation of the Fisher-Yates shuffling algorithm
    for(size_t i = 0; i < n_elements - 1; i++){
        rand_idx = Randomizer_C_gen_integral_range(rndc, i, (n_elements - 1));
        memcpy((uint8_t*)buff, (uint8_t*)array + (i * elem_size), elem_size);
        memcpy((uint8_t*)array + (i * elem_size), (uint8_t*)array + (rand_idx * elem_size), elem_size);
        memcpy((uint8_t*)array + (rand_idx * elem_size), (uint8_t*)buff, elem_size);
    }
    free(buff);
    return 0;
}
#ifdef __cplusplus
}
#endif

#endif // ifndef RANDOMIZER_C