#include "dice.hpp"

namespace mechanics{

Dice::Dice(size_t W): W_(W){
    dist_ = std::uniform_int_distribution<>(1, W);
    seed_ = generate_seed();
    int rnd = dist_(seed_);
}

int Dice::roll(){
    return dist_(seed_);
}

std::mt19937 Dice::generate_seed(){
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen;
}

} //namespace mechanics