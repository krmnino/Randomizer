#ifndef RANDOMIZER
#define RANDOMIZER

#include <stdint.h>
#include <cstring>
#include <sstream>

class Randomizer{
    private:
    uint32_t root_seed;
    uint32_t branching_seed;
    static Randomizer* rnd_ptr;
    
    Randomizer();
    Randomizer(const Randomizer&) = delete;
    Randomizer& operator=(const Randomizer&) = delete;
    uint32_t c11_minstd(uint32_t);
    uint32_t c11_minstd_backwards(uint32_t);
    
    public:
    static Randomizer* get_instance(uint32_t input_seed){
        if(rnd_ptr == nullptr){
            rnd_ptr = new Randomizer();
        }
        rnd_ptr->root_seed = input_seed;
        rnd_ptr->branching_seed = rnd_ptr->c11_minstd(rnd_ptr->root_seed);
        return rnd_ptr;
    } 

    static void end_instance(){
        delete rnd_ptr;
    }

    void root_seed_next();
    void root_seed_prev();
    std::string gen_random_string(size_t, const char*);
    std::string gen_random_string(size_t, std::string&);
    double gen_double_not_nan();
    double gen_double_not_nan_range(double, double);

    template<typename T> T gen_random_integral(){
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

    template<typename T> T gen_random_integral_range(T lower, T upper){
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
};

#endif