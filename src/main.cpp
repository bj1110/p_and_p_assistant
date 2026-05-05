#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include "gameboard/gameboard.hpp"

int main(){
    gameboard::Gameboard gameboard{};
    gameboard.init(2, {2, 8, 10, 20, 100});
    gameboard.roll_dice(20);
    gameboard.roll_dice(22); 
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