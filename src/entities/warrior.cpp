#include "warrior.hpp"

namespace entities{

Warrior::Warrior(const std::string& name) : Character(name, 70, 80, 60, 50) {}

int Warrior::attack () const{
    // throw dice 
    // calculate damage --> need weapon 
    return -1; 
}


}//namespace entities