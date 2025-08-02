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
    
    Randomizer(){
        this->root_seed = 0;
        this->branching_seed = 0;
    }

    Randomizer(const Randomizer&) = delete;
    Randomizer& operator=(const Randomizer&) = delete;

    uint32_t c11_minstd(uint32_t seed){
        int32_t ret = (48271 * (seed % 44488)) - (3399 * (seed / 44488));
        return ret < 0 ? ret + (0x80000000 - 1) : ret;
    }
    
    uint32_t c11_minstd_backwards(uint32_t seed){
        return -247665088 * seed % (0x80000000 - 1);
    }    
    
    public:
    static Randomizer* Randomizer_get_instance(uint32_t input_seed){
        if(rnd_ptr == nullptr){
            rnd_ptr = new Randomizer();
        }
        rnd_ptr->root_seed = input_seed;
        rnd_ptr->branching_seed = rnd_ptr->c11_minstd(rnd_ptr->root_seed);
        return rnd_ptr;
    } 

    static void Randomizer_end_instance(){
        delete rnd_ptr;
    }

    void root_seed_next(){
        this->root_seed = c11_minstd(this->root_seed);
        this->branching_seed = c11_minstd(this->root_seed);
    }

    void root_seed_prev(){
        this->root_seed = c11_minstd_backwards(this->root_seed);
        this->branching_seed = c11_minstd_backwards(this->root_seed);
    }

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

    std::string gen_random_string(size_t length){
        const char* ascii_chars = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
        std::stringstream buffer;
        for(uint32_t i = 0; i < length; i++){
            buffer << (char)ascii_chars[this->gen_random_integral_range<size_t>(0, strlen(ascii_chars) - 1)];
        }
        return buffer.str();
    }
    
    double gen_double_not_nan(){
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

    double gen_double_not_nan_range(double lower, double upper){
        double ret;
        while (true){
            ret = gen_double_not_nan();
            if(lower <= ret && ret <= upper){
                break;
            }
        }
        return ret;
    }
};

#endif