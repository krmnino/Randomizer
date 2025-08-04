#include "Randomizer.hpp"

Randomizer::Randomizer(){
    this->root_seed = 0;
    this->branching_seed = 0;
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

std::string Randomizer::gen_random_string(size_t out_str_length, const char* dictionary){
    if(out_str_length == 0 || strlen(dictionary) == 0){
        return "";
    }
    std::stringstream buffer;
    for(uint32_t i = 0; i < out_str_length; i++){
        buffer << (char)dictionary[this->gen_random_integral_range<size_t>(0, strlen(dictionary) - 1)];
    }
    return buffer.str();
}

std::string Randomizer::gen_random_string(size_t out_str_length, std::string& dictionary){
    return this->gen_random_string(out_str_length, dictionary.c_str());
}

double Randomizer::gen_double_not_nan(){
    union{
        uint64_t rand_buff_u64;
        uint8_t rand_buff_u8[8];
        double rand_buff_double;
    } buff;
    while (true){
        for(size_t i = sizeof(double); i > 0; i--){
            buff.rand_buff_u8[i - 1] = this->gen_random_integral_range<uint8_t>(0x0, 0xFF);
        }
        // Prevent NaN and infinity results
        if((buff.rand_buff_u64 & 0x7FF0000000000000) != 0x7FF0000000000000){
            break;
        }
        break;
    }
    return buff.rand_buff_double;
}

double Randomizer::gen_double_not_nan_range(double lower, double upper){
    double ret;
    while (true){
        ret = gen_double_not_nan();
        if(lower <= ret && ret <= upper){
            break;
        }
    }
    return ret;
}