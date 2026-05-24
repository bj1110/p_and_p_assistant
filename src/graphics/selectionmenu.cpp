#include "selectionmenu.hpp"


namespace graphics
{


SelectionMenu::SelectionMenu(std::shared_ptr<core::Settings> settings, const std::vector<SelectionMenuEntry>& entries, sf::Vector2f position, sf::Vector2f size_per_element, sf::Vector2f margin) 
:settings_(settings), entries_(entries), position_(position), size_per_element_(size_per_element), margin_(margin){
    LOG_INFO("Initilizing Selection Menu"); 
    size_t num_opts = entries.size(); 

    background_.setSize({size_per_element.x +margin.x, (num_opts * size_per_element_.y) + margin.y});
    background_.setFillColor(sf::Color::White);
    background_.setPosition(position_); 
    for(auto& entry:entries_){
        sf::Text& txt = entry.text; 
        txt.setPosition(position_+margin_); 
        txt.setFillColor(sf::Color::Blue); 
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
        if(entries_.at(i).text.getGlobalBounds().contains(mouse_pos)){
            entries_.at(i).callback(event, this->shared_from_this(), i);
        }
    }
}

void SelectionMenu::highlightSelection(size_t idx){
    if(idx >= entries_.size()){
        LOG_ERROR("Access beyond entriey boundaries");
        return;
    }
    sf::Text& txt = entries_.at(idx).text; 
    txt.setOutlineColor(sf::Color::Red);
    txt.setOutlineThickness(3); 

}

void SelectionMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(background_); 
    for(const SelectionMenuEntry& entry:  entries_){
        target.draw(entry.text);
    }
}




    
} // namespace graphics
