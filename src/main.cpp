#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>

int main(){
    entities::Warrior w {"W1"};
    LOG_INFO(w.name);
    mechanics::Dice W10 {10};
    std::ostringstream oss;
    for(int i=0; i<10; ++i){
        oss <<  W10.roll() << ", ";
    }
    LOG_WARN(oss.str()); 
    LOG_ERROR("hallo"); 
    return 0;
}