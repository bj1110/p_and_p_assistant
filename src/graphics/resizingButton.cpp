#include "resizingButton.hpp"

namespace graphics{

resizingButton::resizingButton(sf::Font& font, const std::string& text, sf::Vector2f pos, std::function<void()> callback)
: ButtonTemplate::ButtonTemplate(font, text, pos, callback){
    resize(); 
}


void resizingButton::resize(){
    sf::FloatRect bounds= text_.getLocalBounds();
    shape_.setRectangleSize(bounds.getSize() + sf::Vector2f{10.f, 20.f});
}  

} //namespace graphics 