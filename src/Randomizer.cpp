#include "Randomizer.hpp"
#include "Randomizer_C.h"

Randomizer::Randomizer(){
    this->root_seed = 1;
    this->branching_seed = this->c11_minstd(this->root_seed);
}


Randomizer::Randomizer(uint32_t input_seed){
    this->root_seed = input_seed;
    this->branching_seed = this->c11_minstd(this->root_seed);
}


uint32_t Randomizer::c11_minstd(uint32_t seed){
    int32_t ret = (48271 * (seed % 44488)) - (3399 * (seed / 44488));
    return ret < 0 ? ret + (0x80000000 - 1) : ret;
}


uint32_t Randomizer::c11_minstd_backwards(uint32_t seed){
    return -247665088 * seed % (0x80000000 - 1);
}    


void Randomizer::root_seed_next(){
    this->root_seed = c11_minstd(this->root_seed);
    this->branching_seed = c11_minstd(this->root_seed);
}


void Randomizer::root_seed_prev(){
    this->root_seed = c11_minstd_backwards(this->root_seed);
    this->branching_seed = c11_minstd_backwards(this->root_seed);
}


uint32_t Randomizer::get_root_seed(){
    return this->root_seed;
}


uint32_t Randomizer::get_branching_seed(){
    return this->branching_seed;
}


bool Randomizer::gen_bool(){
    return (this->gen_integral_range<uint8_t>(0, 1) == 0) ? false : true;
}


std::string Randomizer::gen_string(size_t out_str_length, const char* dictionary){
    const char* default_ascii_dict =  "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    if(dictionary == nullptr || out_str_length == 0 || strlen(dictionary) == 0){
        dictionary = default_ascii_dict;
    }
    std::stringstream buffer;
    for(uint32_t i = 0; i < out_str_length; i++){
        buffer << (char)dictionary[this->gen_integral_range<size_t>(0, strlen(dictionary) - 1)];
    }
    return buffer.str();
}


std::string Randomizer::gen_string(size_t out_str_length, std::string& dictionary){
    return this->gen_string(out_str_length, dictionary.c_str());
}


float Randomizer::gen_float(){
    union{
        uint32_t rand_buff_u32;
        float rand_buff_float;
    } buff;
    buff.rand_buff_u32 = this->gen_integral<uint32_t>();
    buff.rand_buff_u32 = (buff.rand_buff_u32 & 0x00FFFFFF) | 0x3F800000;
    buff.rand_buff_float = buff.rand_buff_float - 1.0f;
    return buff.rand_buff_float;
}


float Randomizer::gen_float_range(float lower, float upper){
    union{
        uint32_t rand_buff_u32;
        float rand_buff_float;
    } buff;
    buff.rand_buff_float = this->gen_float();
    buff.rand_buff_float = lower + (buff.rand_buff_float * (upper - lower));
    return buff.rand_buff_float;
}

///////////////////////////////////////////////////////////////
// C INTERFACE DEFINITION 
///////////////////////////////////////////////////////////////

Randomizer_C* Randomizer_C_init(uint32_t input_seed){
    return reinterpret_cast<Randomizer_C*>(new Randomizer(input_seed));
}


int Randomizer_C_delete(Randomizer_C* rndc){
    if(rndc == nullptr){
        return -1;
    }
    delete reinterpret_cast<Randomizer*>(rndc);
    return 0;
}


void Randomizer_C_root_seed_next(Randomizer_C* rndc){
    return reinterpret_cast<Randomizer*>(rndc)->root_seed_next();
}


void Randomizer_C_root_seed_prev(Randomizer_C* rndc){
    return reinterpret_cast<Randomizer*>(rndc)->root_seed_prev();
}


uint32_t Randomizer_C_get_root_seed(Randomizer_C* rndc){
    return reinterpret_cast<Randomizer*>(rndc)->get_root_seed();
}


uint32_t Randomizer_C_get_branching_seed(Randomizer_C* rndc){
    return reinterpret_cast<Randomizer*>(rndc)->get_branching_seed();
}


bool Randomizer_C_gen_bool(Randomizer_C* rndc){
    return reinterpret_cast<Randomizer*>(rndc)->gen_bool();
}


int Randomizer_C_gen_string(Randomizer_C* rndc, char* output_str, size_t out_str_length, const char* dictionary){
    if(output_str == NULL){
        return -1;
    }
    std::string random_str = reinterpret_cast<Randomizer*>(rndc)->gen_string(out_str_length, dictionary);
    memcpy(output_str, random_str.c_str(), out_str_length);
    return 0;
}


float Randomizer_C_gen_float(Randomizer_C* rndc){
    return reinterpret_cast<Randomizer*>(rndc)->gen_float();
}


float Randomizer_C_gen_float_range(Randomizer_C* rndc, float lower, float upper){
    return reinterpret_cast<Randomizer*>(rndc)->gen_float_range(lower, upper);
}


uint64_t Randomizer_C_gen_integral(Randomizer_C* rndc){
    return reinterpret_cast<Randomizer*>(rndc)->gen_integral<uint64_t>();
}


uint64_t Randomizer_C_gen_integral_range(Randomizer_C* rndc, uint64_t lower, uint64_t upper){
    return reinterpret_cast<Randomizer*>(rndc)->gen_integral_range<uint64_t>(lower, upper);
}


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