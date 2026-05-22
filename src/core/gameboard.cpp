#include "gameboard.hpp"

namespace core
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
        LOG_WARN(std::format("There is no dice with {} amount of sides.", sides));
        return -1;
    }
    int n = dice_.at(sides).roll();
    LOG_DEBUG(std::format("Rolled {}", n)); 
    return n; 
}

const std::unordered_map<u_int, mechanics::Dice> Gameboard::getAllDice() const{
    return dice_; 
}


void Gameboard::add_character(std::unique_ptr<entities::Character> character){
    characters_.emplace_back(std::move(character)); 
} 



} // namespace core
