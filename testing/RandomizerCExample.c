#include <stdio.h>
#include <stdlib.h>

#include "../src/Randomizer_C.h"

#define N_ELEMENTS 20
#define BIG_OBJ_SIZE 0x1000

int main(){
    const char* alphanum_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char* str_buff;
    int ret;
    struct BigObject{
        uint8_t data[BIG_OBJ_SIZE];
    };
    typedef struct BigObject BigObject;
    uint8_t* array_u8;
    uint32_t* array_u32;
    uint64_t* array_u64;
    BigObject* array_bigobj;

    Randomizer_C* rnd = Randomizer_C_get_instance(1);
    
    /*************************************************************************************************************************/
    
    // Generating integer of different sizes
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint8_t #%ld -> %x\n", i + 1, (uint8_t)Randomizer_C_gen_integral(rnd));
    }
    Randomizer_C_root_seed_next(rnd);
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint16_t #%ld -> %x\n", i + 1, (uint16_t)Randomizer_C_gen_integral(rnd));
    }
    Randomizer_C_root_seed_next(rnd);
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint32_t #%ld -> %x\n", i + 1, (uint32_t)Randomizer_C_gen_integral(rnd));
    }
    Randomizer_C_root_seed_next(rnd);
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint64_t #%ld -> %lx\n", i + 1, (uint64_t)Randomizer_C_gen_integral(rnd));
    }
    Randomizer_C_root_seed_next(rnd);
    
    /*************************************************************************************************************************/
    
    // Generating integer in range of different sizes
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint8_t #%ld -> %x\n", i + 1, (uint8_t)Randomizer_C_gen_integral_range(rnd, 0x60, 0xA0));
    }
    Randomizer_C_root_seed_next(rnd);
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint16_t #%ld -> %x\n", i + 1, (uint16_t)Randomizer_C_gen_integral_range(rnd, 0x6000, 0xB000));
    }
    Randomizer_C_root_seed_next(rnd);
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint32_t #%ld -> %x\n", i + 1, (uint32_t)Randomizer_C_gen_integral_range(rnd, 0xABC00000, 0xFA800000));
    }
    Randomizer_C_root_seed_next(rnd);
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint64_t #%ld -> %lx\n", i + 1, (uint64_t)Randomizer_C_gen_integral_range(rnd, 0x1000000000000000, 0x3300000000000000));
    }
    Randomizer_C_root_seed_next(rnd);
    
    /*************************************************************************************************************************/
    
    // Generating string with dictionary as NULL
    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = Randomizer_C_gen_integral_range(rnd, 0, 200);
        str_buff = calloc(out_str_len + 1, sizeof(char));
        ret = Randomizer_C_gen_string(rnd, str_buff, out_str_len, NULL);
        if(ret != 0){
            return -1;
        }
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, str_buff);
        free(str_buff);
    }
    Randomizer_C_root_seed_next(rnd);
    
    // Generating string with pupulated dictionary
    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = Randomizer_C_gen_integral_range(rnd, 0, 200);
        str_buff = calloc(out_str_len + 1, sizeof(char));
        ret = Randomizer_C_gen_string(rnd, str_buff, out_str_len, alphanum_chars);
        if(ret != 0){
            return -1;
        }
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, str_buff);
        free(str_buff);
    }
    Randomizer_C_root_seed_next(rnd);
    
    /*************************************************************************************************************************/

    // Generating floating point number
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom double #%ld -> %lf\n", i + 1, Randomizer_C_gen_double_not_nan(rnd));
    }
    Randomizer_C_root_seed_next(rnd);
    
    // Generating floating point number in range
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom range double #%ld -> %lf\n", i + 1, Randomizer_C_gen_double_not_nan_range(rnd, 1.0, 2.0));
    }
    Randomizer_C_root_seed_next(rnd);

    /*************************************************************************************************************************/
    
    // Generating boolean
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom bool #%ld -> %s\n", i + 1, Randomizer_C_gen_bool(rnd) ? "true" : "false");
    }
    Randomizer_C_root_seed_next(rnd);
    
    /*************************************************************************************************************************/

    // Shuffling array of uint8_t
    array_u8 = (uint8_t*)malloc(N_ELEMENTS);
    for(size_t i = 0; i < N_ELEMENTS; i++){
        array_u8[i] = i + 1;
    }
    printf("Array of uint8_t [BEFORE]: [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%d", array_u8[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    Randomizer_C_shuffle(rnd, array_u8, N_ELEMENTS, sizeof(uint8_t));
    printf("Array of uint8_t [AFTER]:  [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%d", array_u8[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    free(array_u8);
    Randomizer_C_root_seed_next(rnd);

    /*************************************************************************************************************************/

    // Shuffling array of uint32_t
    array_u32 = (uint32_t*)malloc(N_ELEMENTS);
    for(size_t i = 0; i < N_ELEMENTS; i++){
        array_u32[i] = i + 1;
    }
    printf("Array of uint32_t [BEFORE]: [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%d", array_u32[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    Randomizer_C_shuffle(rnd, array_u32, N_ELEMENTS, sizeof(uint32_t));
    printf("Array of uint32_t [AFTER]:  [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%d", array_u32[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    free(array_u32);
    Randomizer_C_root_seed_next(rnd);

    /*************************************************************************************************************************/

    // Shuffling array of uint64_t
    array_u64 = (uint64_t*)malloc(N_ELEMENTS);
    for(size_t i = 0; i < N_ELEMENTS; i++){
        array_u64[i] = i + 1;
    }
    printf("Array of uint64_t [BEFORE]: [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%ld", array_u64[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    Randomizer_C_shuffle(rnd, array_u64, N_ELEMENTS, sizeof(uint64_t));
    printf("Array of uint64_t [AFTER]:  [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%ld", array_u64[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    free(array_u64);
    Randomizer_C_root_seed_next(rnd);

    /*************************************************************************************************************************/
    
    // Shuffling array of BigObjects
    array_bigobj = (BigObject*)malloc(sizeof(BigObject) * N_ELEMENTS);
    for(size_t i = 0; i < N_ELEMENTS; i++){
        for(size_t j = 0; j < BIG_OBJ_SIZE; j++){
            array_bigobj[i].data[j] = (uint8_t)i;
        }
    }
    printf("Array of BigObj [BEFORE]:\n");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("\n\nElement# %ld\n", i);
        for(size_t j = 0; j < BIG_OBJ_SIZE; j++){
            if(j != 0 && j % 64 == 0){
                printf("\n");
            }
            if(array_bigobj[i].data[j] < 0xa){
                printf("0");
            }
            printf("%d", array_bigobj[i].data[j]);
        }
    }
    printf("\n");
    Randomizer_C_shuffle(rnd, array_bigobj, N_ELEMENTS, sizeof(BigObject));
    printf("Array of BigObj [AFTER]:\n");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("\n\nElement# %ld\n", i);
        for(size_t j = 0; j < BIG_OBJ_SIZE; j++){
            if(j != 0 && j % 64 == 0){
                printf("\n");
            }
            if(array_bigobj[i].data[j] < 0xa){
                printf("0");
            }
            printf("%d", array_bigobj[i].data[j]);
        }
    }
    printf("\n");
    free(array_bigobj);
    Randomizer_C_root_seed_next(rnd);

    return 0;
}