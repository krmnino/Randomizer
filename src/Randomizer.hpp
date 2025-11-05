#ifndef RANDOMIZER
#define RANDOMIZER

#include <stdint.h>
#include <cstring>
#include <sstream>
#include <vector>
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
    double gen_double_not_nan();
    double gen_double_not_nan_range(double, double);
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
};

#endif