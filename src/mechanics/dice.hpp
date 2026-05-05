#pragma once 
#include <stddef.h>
#include <random>

namespace mechanics{

class Dice{
public:
    Dice(u_int);

    int roll();

private:
    size_t W_; 
    std::uniform_int_distribution<> dist_; 
    std::mt19937 seed_; 
    std::mt19937 generate_seed();
};  



} //namespace mechanics