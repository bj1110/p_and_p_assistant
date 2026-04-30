#include <iostream>
#include "entities/warrior.hpp"

int main(){
    entities::Warrior w {"W1"};
    std::cout << w.name <<std::endl; 
    return 0;
}