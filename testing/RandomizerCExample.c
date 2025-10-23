#include <stdio.h>

#include "../src/Randomizer_C.h"

int main(){
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
        printf("Pseudorandom bool #%ld -> %s\n", i + 1, Randomizer_C_bool_gen_bool(rnd) ? "true" : "false");
    }
    Randomizer_C_root_seed_next(rnd);
}