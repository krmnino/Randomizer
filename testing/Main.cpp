#include "../src/Randomizer.hpp"
#include <iostream>

Randomizer* Randomizer::rnd_ptr = nullptr;

int main(){
    std::string ascii_chars = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    std::string alphanum_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    Randomizer* rnd = Randomizer::get_instance(1);
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
        size_t out_str_len = rnd->gen_random_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, rnd->gen_random_string(out_str_len, ascii_chars).c_str());
    }

    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = rnd->gen_random_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, rnd->gen_random_string(out_str_len, alphanum_chars).c_str());
    }

    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = rnd->gen_random_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, rnd->gen_random_string(out_str_len, ascii_chars.c_str()).c_str());
    }

    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = rnd->gen_random_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, rnd->gen_random_string(out_str_len, alphanum_chars.c_str()).c_str());
    }
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom double #%ld -> %lf\n", i + 1, rnd->gen_double_not_nan());
    }
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom range double #%ld -> %lf\n", i + 1, rnd->gen_double_not_nan_range(1.0, 2.0));
    }

    Randomizer::end_instance();
    return 0;
}