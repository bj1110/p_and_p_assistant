#include "dicemenu.hpp"

namespace graphics{

DiceMenu::DiceMenu(std::shared_ptr<core::Settings> settings, std::shared_ptr<core::Gameboard> gameboard, sf::Vector2f btn_size, sf::Vector2f margin):
settings_(settings), gameboard_(gameboard), button_sizes_(btn_size)
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
        auto btn = std::make_unique<FixedSizeButton>(settings->font, "Click here to roll a W"+ std::to_string(sides), btn_pos, btn_size);
        btn->setCallback(createButtonLambda(sides)); 
        buttons_.emplace_back(std::move(btn)); 
        ++curr_btn_num; 
    }
    expandButton_ =  std::make_unique<ResizingButton>(settings->font, ">", sf::Vector2f{0.f, settings_->windowsize.y/2.f}, [this]()
    {   
        hide_menu_=!hide_menu_;
        sf::Vector2f btn_size = expandButton_->getSize();
        sf::Vector2f expandedPos {button_sizes_.x + btn_size.x, settings_->windowsize.y/2.f}; 
        expandButton_->setPosition(hide_menu_? sf::Vector2f{0.f, settings_->windowsize.y/2.f} : expandedPos); 
    }); 
    result_button_ = std::make_unique<FixedSizeButton>(settings->font, "", sf::Vector2f{margin.x, static_cast<float>(curr_btn_num) * (btn_size.y + margin.y) + (margin.y)}, btn_size); 
}


std::function<void()> DiceMenu::createButtonLambda(u_int sides) const{
    return [this, sides](){
        u_int rnd = gameboard_->roll_dice(sides); 
        result_button_->setString(std::format("your W{} rolled: {}",sides, rnd)); 
    };
}

void DiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*expandButton_);
    if(hide_menu_){
        return;
    }
    for(const auto& btn: buttons_){
        target.draw(*btn);
    }
    target.draw(*result_button_); 
}

void DiceMenu::handleEvent(const sf::Event& event){
    for(const auto& btn: buttons_){
        btn->handleEvent(event); 
    }
    expandButton_->handleEvent(event); 
}



} // namespace graphics