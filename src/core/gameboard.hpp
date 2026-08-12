#pragma once

#include <vector>
#include "entities/character.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include "graphics/inputPopUp.hpp"
#include "settings.hpp"
#include "graphics/GUI_manager.hpp"
#include "graphics/components/resizingButton.hpp"

namespace core{

class Gameboard {
public:
    Gameboard() = default;
    Gameboard(std::shared_ptr<Settings> settings, std::shared_ptr<graphics::GUI_manager> gui_manager);

    void init(u_int num_players, const std::vector<u_int>& dice);

    int roll_dice(u_int sides);
    const std::unordered_map<u_int, mechanics::Dice> getAllDice() const;

    [[nodiscard]] bool add_character(std::shared_ptr<entities::Character> character); 

    std::shared_ptr<entities::Character> getCharater(const std::string& name);

    void create_character(); 

private:

    std::unordered_map<std::string, std::shared_ptr<entities::Character>> m_characters {};
    std::unordered_map<u_int, mechanics::Dice> m_dice {}; 
    u_int m_num_players = 0;
    std::shared_ptr<Settings> m_settings = nullptr; 
    std::shared_ptr<graphics::GUI_manager> m_gui_manager = nullptr; 

    std::unordered_set<std::string> m_stats {};

};




} //namespace core