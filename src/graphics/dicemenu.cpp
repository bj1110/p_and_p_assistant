#include "dicemenu.hpp"

namespace graphics{

DiceMenu::DiceMenu(const sf::Font& font, std::shared_ptr<gameboard::Gameboard> gameboard, sf::Vector2f btn_size, sf::Vector2f margin):
gameboard_(gameboard), button_sizes_(btn_size)
{
    LOG_INFO("Initializing Dice Menu");
    int curr_btn_num=0; 
    const auto dice = gameboard_ -> getAllDice(); 
    std::vector<u_int> sides_numbers {};
    for(const auto& [sides, d]: dice){
        sides_numbers.push_back(sides);
    }
    std::sort(sides_numbers.begin(), sides_numbers.end());
    for(const auto& sides: sides_numbers){
        sf::Vector2f btn_pos = {margin.x, (static_cast<float>(curr_btn_num) * (btn_size.y + margin.y)) + (margin.y)}; 
        LOG_DEBUG(std::format("Initializing Button for Dice with {} sides at {}", sides, to_string(btn_pos)));
        auto btn = std::make_unique<FixedSizeButton>(font, "Click here to roll a W"+ std::to_string(sides), btn_pos, btn_size);
        btn->setCallback(createButtonLambda(btn.get(), sides)); 
        buttons_.emplace_back(std::move(btn)); 
        ++curr_btn_num; 
    }
}


std::function<void()> DiceMenu::createButtonLambda(FixedSizeButton* btn, u_int sides) const{
    return [this, btn, sides](){
        u_int rnd = gameboard_->roll_dice(sides); 
        btn->setString(std::format("you rolled: {}", rnd)); 
    };
}

void DiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(const auto& btn: buttons_){
        target.draw(*btn);
    }
}

void DiceMenu::handleEvent(const sf::Event& event){
    for(const auto& btn: buttons_){
        btn->handleEvent(event); 
    }
}



} // namespace graphics