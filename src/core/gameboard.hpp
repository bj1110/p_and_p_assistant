#pragma once

#include <vector>
#include "entities/character.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <unordered_map>
#include <memory>

namespace core{

class Gameboard {
public:
    Gameboard() = default;

    void init(u_int num_players, const std::vector<u_int>& dice);

    int roll_dice(u_int sides);
    const std::unordered_map<u_int, mechanics::Dice> getAllDice() const;

private:

    std::vector<entities::Character> characters_;
    std::unordered_map<u_int, mechanics::Dice> dice_; 
    u_int num_players_ = 0;


};




} //namespace core