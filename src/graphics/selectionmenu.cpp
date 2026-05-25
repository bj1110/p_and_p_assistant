#include "selectionmenu.hpp"


namespace graphics
{


SelectionMenu::SelectionMenu(std::shared_ptr<core::Settings> settings, const std::vector<std::string>& items, sf::Vector2f position, sf::Vector2f size_per_element, sf::Vector2f margin) 
:settings_(settings), position_(position), size_per_element_(size_per_element), margin_(margin){
    LOG_INFO("Initilizing Selection Menu"); 
    int elem_num=0;  
    for(auto& item:items){
        sf::Vector2f elem_pos = {position};
        elem_pos.y += (static_cast<float>(elem_num)* (size_per_element.y + 2.f*margin_.y) ); 
        auto btn = std::make_unique<FixedSizeButton> (settings_->font, item, elem_pos, size_per_element_ , createLambda());
        btn->setShapesCornerSharpeness(300.f); 
        btn->setButtonColor(sf::Color::White);
        btn->setTextColor(sf::Color::Black); 
        buttons_.emplace_back(std::move(btn));
        elem_num++; 
    }
}

void SelectionMenu::handleEvent(const sf::Event& event){
    sf::Vector2f mouse_pos;
    switch (event.type){
        case sf::Event::MouseMoved:
            mouse_pos = {static_cast<float>(event.mouseMove.x), 
                        static_cast<float>(event.mouseMove.y)};
            break;
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            mouse_pos = {static_cast<float>(event.mouseButton.x),
                        static_cast<float>(event.mouseButton.y)};
            break;
        default: return; 
    } 
    for(auto& btn: buttons_){
        btn->handleEvent(event); 
    }
}

void SelectionMenu::highlightSelection(size_t idx){
    if(idx >= buttons_.size()){
        LOG_ERROR("Access beyond entriey boundaries");
        return;
    }
    auto& btn = buttons_.at(idx);
    if(btn->getButtonColor() == sf::Color::Red){
        btn->setButtonColor(sf::Color::White);
    }else{
        btn->setButtonColor(sf::Color::Red);
    }
}

void SelectionMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& button:  buttons_){
        target.draw(*button); 
    }
}

ButtonTemplate::ButtonCallback SelectionMenu::createLambda(){
    return [this](ButtonTemplate& btn){
        auto fixed = dynamic_cast<FixedSizeButton&>(btn);
        if(&btn == selected_){
            btn.setButtonColor(sf::Color::White);
            selected_ = nullptr;
        }
        else{
            if(selected_){
                selected_->setButtonColor(sf::Color::White);
            }
            btn.setButtonColor(sf::Color::Red);
            selected_ = &btn;
        }
    };
}



    
} // namespace graphics
