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

    [[nodiscard]] bool add_character(std::shared_ptr<entities::Character> character); 

    std::shared_ptr<entities::Character> getCharater(const std::string& name);

private:

    std::unordered_map<std::string, std::shared_ptr<entities::Character>> m_characters {};
    std::unordered_map<u_int, mechanics::Dice> m_dice {}; 
    u_int m_num_players = 0;


};




} //namespace core