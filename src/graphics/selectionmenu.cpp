#include "selectionmenu.hpp"


namespace graphics
{


SelectionMenu::SelectionMenu(std::shared_ptr<core::Settings> settings, const std::vector<SelectionMenuItem>& items, sf::Vector2f position, sf::Vector2f size_per_element, sf::Vector2f margin) 
:settings_(settings), position_(position), size_per_element_(size_per_element), margin_(margin){
    LOG_INFO("Initilizing Selection Menu"); 
    int elem_num=0;  
    for(auto& item:items){
        sf::Text text {item.text,settings->font, 20};
        sf::Vector2f elem_pos = {position};
        elem_pos.y += (static_cast<float>(elem_num)* (size_per_element.y + 2.f*margin_.y) ); 
        text.setPosition(elem_pos +margin_); 
        text.setFillColor(sf::Color::Black); 
        sf::RectangleShape rect {size_per_element_ +2.f*margin_};
        rect.setPosition(elem_pos);
        rect.setFillColor(sf::Color::White);
        entries_.emplace_back(text, item.callback, rect);
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
    for(size_t i=0; i<entries_.size(); ++i){
        if(entries_.at(i).text_box.getGlobalBounds().contains(mouse_pos)){
            entries_.at(i).callback(event, this->shared_from_this(), i);
        }
    }
}

void SelectionMenu::highlightSelection(size_t idx){
    if(idx >= entries_.size()){
        LOG_ERROR("Access beyond entriey boundaries");
        return;
    }
    sf::RectangleShape& textbox = entries_.at(idx).text_box;
    textbox.setOutlineColor(sf::Color::Red);
    if(textbox.getOutlineThickness() == 0.f){
        textbox.setOutlineThickness(-4.f);
    }else{
        textbox.setOutlineThickness(0.f);
    }
}

void SelectionMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const SelectionMenuEntry& entry:  entries_){
        target.draw(entry.text_box); 
        target.draw(entry.text);
    }
}




    
} // namespace graphics
