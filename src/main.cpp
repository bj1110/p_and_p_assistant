#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>

int main(){
    utils::Logger logger {utils::LogLevel::Info}; 
    entities::Warrior w {"W1"};
    logger.log(w.name);
    mechanics::Dice W10 {10};
    std::ostringstream oss;
    for(int i=0; i<10; ++i){
        oss <<  W10.roll() << ", ";
    }
    logger.log(oss.str()); 
    logger.changeLogLevel(utils::LogLevel::Debug);
    logger.log("Hallo"); 
    return 0;
}