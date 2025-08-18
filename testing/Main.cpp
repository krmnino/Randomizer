#include "../src/Randomizer.hpp"

#define N_ELEMENTS 20
#define BIG_OBJ_SIZE 0x1000
#define BYTES_PER_LINE 64
#define MAX_STR_LEN 8

Randomizer* Randomizer::rnd_ptr = nullptr;

int main(){
    std::string alphanum_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string empty_str = "";
    std::stringstream buffer;
    struct BigObject{
        uint8_t data[BIG_OBJ_SIZE];
    };
    typedef struct BigObject BigObject;
    uint8_t* array_u8;
    uint32_t* array_u32;
    uint64_t* array_u64;
    BigObject* array_bigobj;
    char** array_charptrs;

    Randomizer* rnd = Randomizer::get_instance(1);
    if(rnd == nullptr){
        printf("Could not initialize Randomizer object.\n");
        return -1;
    }

    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint8_t #%ld -> %x\n", i + 1, rnd->gen_integral<uint8_t>());
    }
    rnd->root_seed_next();
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint16_t #%ld -> %x\n", i + 1, rnd->gen_integral<uint16_t>());
    }
    rnd->root_seed_next();
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint32_t #%ld -> %x\n", i + 1, rnd->gen_integral<uint32_t>());
    }
    rnd->root_seed_next();
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint64_t #%ld -> %lx\n", i + 1, rnd->gen_integral<uint64_t>());
    }
    rnd->root_seed_next();
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint8_t #%ld -> %x\n", i + 1, rnd->gen_integral_range<uint8_t>(0x60, 0xA0));
    }
    rnd->root_seed_next();
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint16_t #%ld -> %x\n", i + 1, rnd->gen_integral_range<uint16_t>(0x6000, 0xB000));
    }
    rnd->root_seed_next();
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint32_t #%ld -> %x\n", i + 1, rnd->gen_integral_range<uint32_t>(0xABC00000, 0xFA800000));
    }
    rnd->root_seed_next();
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom uint64_t #%ld -> %lx\n", i + 1, rnd->gen_integral_range<uint64_t>(0x1000000000000000, 0x3300000000000000));
    }
    rnd->root_seed_next();
    
    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = rnd->gen_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, rnd->gen_string(out_str_len, empty_str).c_str());
    }
    rnd->root_seed_next();
    
    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = rnd->gen_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, rnd->gen_string(out_str_len, alphanum_chars).c_str());
    }
    rnd->root_seed_next();
    
    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = rnd->gen_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, rnd->gen_string(out_str_len, nullptr).c_str());
    }
    rnd->root_seed_next();
    
    for(size_t i = 0; i < 20; i++){
        size_t out_str_len = rnd->gen_integral_range<uint32_t>(0, 200);
        printf("Pseudorandom string #%ld -> Length: %ld -> %s\n", i + 1, out_str_len, rnd->gen_string(out_str_len, alphanum_chars.c_str()).c_str());
    }
    rnd->root_seed_next();
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom double #%ld -> %lf\n", i + 1, rnd->gen_double_not_nan());
    }
    rnd->root_seed_next();
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom range double #%ld -> %lf\n", i + 1, rnd->gen_double_not_nan_range(1.0, 2.0));
    }
    rnd->root_seed_next();
    
    for(size_t i = 0; i < 20; i++){
        printf("Pseudorandom bool #%ld -> %s\n", i + 1, rnd->gen_bool() ? "true" : "false");
    }
    rnd->root_seed_next();
    
    // Shuffling array of uint8_t
    array_u8 = new uint8_t[20];
    for(size_t i = 0; i < N_ELEMENTS; i++){
        array_u8[i] = i + 1;
    }
    printf("List of uint8_t [BEFORE]: [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%d", array_u8[i]);
        if(i < N_ELEMENTS -1){
            printf(",");
        }
    }
    printf("]\n");
    rnd->shuffle(array_u8, N_ELEMENTS, sizeof(uint8_t));
    printf("List of uint8_t [AFTER]:  [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%d", array_u8[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    delete[] array_u8;
    rnd->root_seed_next();
    
    // Shuffling array of uint32_t
    array_u32 = new uint32_t[20];
    for(size_t i = 0; i < N_ELEMENTS; i++){
        array_u32[i] = (i + 1) * 2;
    }
    printf("List of uint32_t [BEFORE]: [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%d", array_u32[i]);
        if(i < N_ELEMENTS -1){
            printf(",");
        }
    }
    printf("]\n");
    rnd->shuffle(array_u32, N_ELEMENTS, sizeof(uint32_t));
    printf("List of uint32_t [AFTER]:  [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%d", array_u32[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    delete[] array_u32;
    rnd->root_seed_next();

    // Shuffling array of uint64_t
    array_u64 = new uint64_t[20];
    for(size_t i = 0; i < N_ELEMENTS; i++){
        array_u64[i] = (i + 1) * 2;
    }
    printf("List of uint64_t [BEFORE]: [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%ld", array_u64[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    rnd->shuffle(array_u64, N_ELEMENTS, sizeof(uint64_t));
    printf("List of uint64_t [AFTER]:  [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("%ld", array_u64[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    delete[] array_u64;
    rnd->root_seed_next();
    
    // Shuffling array of BigObjects
    array_bigobj = new BigObject[N_ELEMENTS];
    for(size_t i = 0; i < N_ELEMENTS; i++){
        for(size_t j = 0; j < BIG_OBJ_SIZE; j++){
            array_bigobj[i].data[j] = (uint8_t)i;
        }
    }
    printf("List of BigObj [BEFORE]:\n");
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
    rnd->shuffle(array_bigobj, N_ELEMENTS, sizeof(BigObject));
    printf("List of BigObj [AFTER]:\n");
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
    delete[] array_bigobj;
    rnd->root_seed_next();

    // Shuffling array of pointers to char* objects
    array_charptrs = new char*[N_ELEMENTS];
    for(size_t i = 0; i < N_ELEMENTS; i++){
        array_charptrs[i] = new char[MAX_STR_LEN + 1];
        memset(array_charptrs[i], 0, MAX_STR_LEN + 1);
        for(size_t j = 0; j < MAX_STR_LEN; j += 2){
            if(i < 0x10 - 1){
                buffer << "0" << std::hex << (i + 1);
            }
            else{
                buffer << std::hex << (i + 1);
            }
        }
        for(size_t j = 0; j < MAX_STR_LEN; j++){
            array_charptrs[i][j] = buffer.str()[j];
        }
        buffer.str("");
        buffer.clear();
    }
    printf("List of char** [BEFORE]: [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("\"%s\"", array_charptrs[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    rnd->shuffle(array_u64, N_ELEMENTS, sizeof(char*));
    printf("List of char** [AFTER] : [");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        printf("\"%s\"", array_charptrs[i]);
        if(i < N_ELEMENTS - 1){
            printf(",");
        }
    }
    printf("]\n");
    for(size_t i = 0; i < N_ELEMENTS; i++){
        delete array_charptrs[i];
    }
    delete[] array_charptrs;
    
    Randomizer::end_instance();
    return 0;
}