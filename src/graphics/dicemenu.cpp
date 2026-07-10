#include "dicemenu.hpp"
#include "graphics/GUI_manager.hpp"

namespace graphics{

DiceMenu::DiceMenu(std::shared_ptr<core::Settings> settings, std::shared_ptr<core::Gameboard> gameboard, sf::Vector2f btn_size, sf::Vector2f margin):
settings_(settings), gameboard_(gameboard), button_sizes_(btn_size), margin_(margin)
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
        btn->setButtonColor(sf::Color(0, 155, 0, 180)); 
        buttons_.emplace_back(std::move(btn)); 
        ++curr_btn_num; 
    }
    expandButton_ =  std::make_unique<ResizingButton>(settings->font, ">", sf::Vector2f{0.f, settings_->windowsize.y/2.f}, [this](ButtonTemplate&)
    {   
        hide_menu_=!hide_menu_;
        sf::Vector2f btn_size = expandButton_->getSize();
        sf::Vector2f expandedPos {button_sizes_.x + 2.f* margin_.x, settings_->windowsize.y/2.f}; 
        expandButton_->setPosition(hide_menu_? sf::Vector2f{0.f, settings_->windowsize.y/2.f} : expandedPos); 
        expandButton_->setString(hide_menu_? ">": "<"); 
        if(!hide_menu_){
            if(auto tmp = manager.lock()){
                tmp->focusElement(this);
            }
        }
        else{
            if(auto tmp = manager.lock()){
                tmp->focusAll();
            }
        }
    }); 
    auto result_button_ = std::make_unique<FixedSizeButton>(settings->font, "", sf::Vector2f{margin.x, static_cast<float>(curr_btn_num) * (btn_size.y + margin.y) + (margin.y)}, btn_size, [](ButtonTemplate&){}); 
    buttons_.emplace_back(std::move(result_button_));
    background_.setSize({button_sizes_.x + 2.f* margin_.x, settings_->windowsize.y* 1.f});
    background_.setPosition({0.f, 0.f}); 
    background_.setFillColor(sf::Color(45, 150, 130, 150));

}


std::function<void(ButtonTemplate&)> DiceMenu::createButtonLambda(u_int sides) const{
    return [this, sides](ButtonTemplate& btn){
        u_int rnd = gameboard_->roll_dice(sides); 
        buttons_.back()->setString(std::format("your W{} rolled: {}",sides, rnd)); 
    };
}

void DiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*expandButton_);
    if(hide_menu_){
        return;
    }
    target.draw(background_); 
    for(const auto& btn: buttons_){
        target.draw(*btn);
    }
}

void DiceMenu::handleEvent(const sf::Event& event){
    expandButton_->handleEvent(event); 
    if(hide_menu_){
        return;
    }
    for(const auto& btn: buttons_){
        btn->handleEvent(event); 
    }
}



} // namespace graphics