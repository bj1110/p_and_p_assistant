#include "selectionmenu.hpp"


namespace graphics
{


SelectionMenu::SelectionMenu(std::shared_ptr<core::Settings> settings, const std::vector<std::string>& descriptors, const std::vector<std::function<void()>>& callbacks, sf::Vector2f positon, sf::Vector2f size_per_element)
:settings_(settings), descriptors_(descriptors), callbacks_(callbacks), position_(positon), size_per_element_(size_per_element){
    LOG_INFO("Initilizing Selection Menu"); 
    size_t num_opts = descriptors.size(); 
    if(num_opts != callbacks.size()){
        LOG_ERROR("Number of options does not equal the number of callbacks");
    }
    background_.setSize({size_per_element.x, num_opts * size_per_element_.y});
    background_.setFillColor(sf::Color::White);
    background_.setPosition(position_); 
    texts_.reserve(num_opts);
    int i=0; 
    for(const std::string& elem: descriptors_){
        sf::Text txt {elem,settings_->font, 20};
        txt.setPosition({position_.x, (i* size_per_element.y)+ position_.y});
        txt.setFillColor(sf::Color::Blue); 
        texts_.emplace_back(txt);
        LOG_INFO(std::format("Position of Text {}, of background {}", to_string(txt.getPosition()), to_string(background_.getPosition()))); 
    }
}


void SelectionMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(background_); 
    for(const sf::Text txt: texts_){
        target.draw(txt);
    }
}



    
} // namespace graphics
