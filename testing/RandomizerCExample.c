#include <stdio.h>
#include <stdlib.h>

#include "../src/Randomizer_C.h"

int main(){
    const char* alphanum_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char* str_buff;
    int ret;

    Randomizer_C* rnd = Randomizer_C_get_instance(1);
    
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

    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom double #%ld -> %lf\n", i + 1, Randomizer_C_gen_double_not_nan(rnd));
    }
    Randomizer_C_root_seed_next(rnd);
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom range double #%ld -> %lf\n", i + 1, Randomizer_C_gen_double_not_nan_range(rnd, 1.0, 2.0));
    }
    Randomizer_C_root_seed_next(rnd);

    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom bool #%ld -> %s\n", i + 1, Randomizer_C_gen_bool(rnd) ? "true" : "false");
    }
    Randomizer_C_root_seed_next(rnd);
}