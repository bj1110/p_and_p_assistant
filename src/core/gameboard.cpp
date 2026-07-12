#include "gameboard.hpp"

namespace core
{

void Gameboard::init(u_int num_players, const std::vector<u_int>& dice){
    LOG_INFO("Initializing Gameboard ..."); 
    m_num_players = num_players;
    for(u_int w: dice){
        mechanics::Dice d {w};
        m_dice.insert({w, d}); 
    }
    LOG_INFO("Gameboard initialized."); 
}

int Gameboard::roll_dice(u_int sides){
    if(!m_dice.contains(sides)){
        LOG_WARN(std::format("There is no dice with {} amount of sides.", sides));
        return -1;
    }
    int n = m_dice.at(sides).roll();
    LOG_DEBUG(std::format("Rolled {}", n)); 
    return n; 
}

const std::unordered_map<u_int, mechanics::Dice> Gameboard::getAllDice() const{
    return m_dice; 
}


bool Gameboard::add_character(std::shared_ptr<entities::Character> character){
    std::string name= character->getName();
    if(m_characters.contains(name)){
        LOG_ERROR("Trying to add Character that already exists");
        return false;
    }
    m_characters.emplace(character->getName(), std::move(character)); 
    return true; 
} 

std::shared_ptr<entities::Character> Gameboard::getCharater(const std::string& name){
    if(m_characters.contains(name)){
        return m_characters[name];
    }
    return nullptr;
}




} // namespace core
