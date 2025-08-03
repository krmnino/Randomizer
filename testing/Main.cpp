#include "../src/Randomizer.hpp"
#include <iostream>

Randomizer* Randomizer::rnd_ptr = nullptr;

int main(){
    Randomizer* rnd = Randomizer::Randomizer_get_instance(1);
    if(rnd == nullptr){
        printf("Could not initialize Randomizer object.\n");
        return -1;
    }

    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint8_t #%ld -> %x\n", i + 1, rnd->gen_random_integral<uint8_t>());
    }
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint16_t #%ld -> %x\n", i + 1, rnd->gen_random_integral<uint16_t>());
    }
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint32_t #%ld -> %x\n", i + 1, rnd->gen_random_integral<uint32_t>());
    }
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint64_t #%ld -> %lx\n", i + 1, rnd->gen_random_integral<uint64_t>());
    }

    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint8_t #%ld -> %x\n", i + 1, rnd->gen_random_integral_range<uint8_t>(0x60, 0xA0));
    }
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint16_t #%ld -> %x\n", i + 1, rnd->gen_random_integral_range<uint16_t>(0x6000, 0xB000));
    }
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint32_t #%ld -> %x\n", i + 1, rnd->gen_random_integral_range<uint32_t>(0xABC00000, 0xFA800000));
    }
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint64_t #%ld -> %lx\n", i + 1, rnd->gen_random_integral_range<uint64_t>(0x1000000000000000, 0x3300000000000000));
    }

    for(size_t i = 0; i < 20; i++){
        size_t str_len = rnd->gen_random_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, str_len, rnd->gen_random_string(str_len).c_str());
    }
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom double #%ld -> %lf\n", i + 1, rnd->gen_double_not_nan());
    }
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom range double #%ld -> %lf\n", i + 1, rnd->gen_double_not_nan_range(1.0, 2.0));
    }

    return 0;
}