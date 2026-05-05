#include "gameboard.hpp"

namespace gameboard
{

void Gameboard::init(u_int num_players, const std::vector<u_int>& dice){
    LOG_INFO("Initializing Gameboard ..."); 
    num_players_ = num_players;
    for(u_int w: dice){
        mechanics::Dice d {w};
        dice_.insert({w, d}); 
    }
    LOG_INFO("Gameboard initialized."); 
}

int Gameboard::roll_dice(u_int sides){
    if(!dice_.contains(sides)){
        LOG_WARN("There is no dice with that amount of sides. Cannot throw");
        return -1;
    }
    return dice_.at(sides).roll(); 
}



} // namespace gameboard
