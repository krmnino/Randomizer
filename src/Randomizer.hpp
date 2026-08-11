#ifndef RANDOMIZER
#define RANDOMIZER

#include <stdint.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <iostream>


class Randomizer{
    private:
    uint32_t root_seed;
    uint32_t branching_seed;
    static Randomizer* rnd_ptr;
    
    uint32_t c11_minstd(uint32_t);
    uint32_t c11_minstd_backwards(uint32_t);
    
    public:
    Randomizer();
    ~Randomizer(){}
    Randomizer(uint32_t);
    Randomizer(const Randomizer&);
    Randomizer& operator=(const Randomizer&);
    void root_seed_next();
    void root_seed_prev();
    uint32_t get_root_seed();
    uint32_t get_branching_seed();
    bool gen_bool();
    std::string gen_string(size_t, const char*);
    std::string gen_string(size_t, std::string&);
    float gen_float();
    float gen_float_range(float, float);
    int shuffle(void*, size_t, size_t);


    template<typename T> T gen_integral(){
        size_t input_size = sizeof(T);
        T accumulator = 0;
        uint8_t random_byte;
        
        // Generate random integer byte by byte
        for(size_t i = 0; i < input_size; i++){
            random_byte = (uint8_t)(this->branching_seed & 0x000000FF);
            this->branching_seed = c11_minstd(this->branching_seed);
            accumulator = accumulator << 8 | random_byte;
        }
        return accumulator;
    }


    template<typename T> T gen_integral_range(T lower, T upper){
        size_t input_size = sizeof(T);
        T accumulator = 0;
        uint8_t random_byte;

        // Check if lower boundary is greater than the higher boundary
        if(upper < lower){
            return (T)0;
        }

        // Generate random integer byte by byte
        for(size_t i = 0; i < input_size; i++){
            random_byte = (uint8_t)(this->branching_seed & 0x000000FF);
            this->branching_seed = c11_minstd(this->branching_seed);
            accumulator = accumulator << 8 | random_byte;
        }
        
        // Keep it in range
        accumulator = (accumulator % (upper - lower + 1)) + lower;
        return accumulator;
    }


    template<typename T> int shuffle(T* array, size_t n_elements){
        size_t rand_idx;

        // Check for zeros or nullptr
        if(array == nullptr || n_elements == 0){
            return -1;
        }
        // Nothing to shuffle
        if(n_elements == 1){
            return 0;
        }
        // Variation of the Fisher-Yates shuffling algorithm
        for(size_t i = 0; i < n_elements - 1; i++){
            rand_idx = gen_integral_range(i, (n_elements - 1));
            std::swap(array[i], array[rand_idx]);
        }
        return 0;
    }


    template<typename T> int shuffle(std::vector<T>& input_vect){
        return shuffle(input_vect.data(), input_vect.size());
    }


    template<typename T> T gen_float(){
        union{
            uint32_t as_int;
            float as_float;
        } buff32;
        union{
            uint64_t as_int;
            double as_double;
        } buff64;
        
        if constexpr (std::is_same_v<T, float>){
            buff32.as_int = this->gen_integral<uint32_t>();
            buff32.as_int = (buff32.as_int & 0x00FFFFFF) | 0x3F800000;
            buff32.as_float = buff32.as_float - 1.0f;
            return buff32.as_float;
        }
        else if constexpr (std::is_same_v<T, double>){
            buff64.as_int = this->gen_integral<uint64_t>();
            buff64.as_int = (buff64.as_int & 0x000FFFFFFFFFFFFF) | 0x3FF0000000000000;
            buff64.as_double = buff64.as_double - 1.0f;
            return buff64.as_double;
        }
        return 0.0f;
    }
    
    
    template<typename T> T gen_float_range(T lower, T upper){
        float rand_float;
        double rand_double;
        if constexpr (std::is_same_v<T, float>){
            rand_float = this->gen_float<float>();
            rand_float = lower + (rand_float * (upper - lower));
            return rand_float;
        }
        else if constexpr (std::is_same_v<T, double>){
            rand_double = this->gen_float<double>();
            rand_double = lower + (rand_double * (upper - lower));
            return rand_double;
        }
        return 0.0f;
    }
};

#endif