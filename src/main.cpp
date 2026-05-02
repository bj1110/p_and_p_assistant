#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"

int main(){
    entities::Warrior w {"W1"};
    std::cout << w.name <<std::endl; 
    mechanics::Dice W10 {10};
    for(int i=0; i<10; ++i){
        std::cout << W10.roll() << ", ";
    }
    std::cout << std::endl; 
    return 0;
}