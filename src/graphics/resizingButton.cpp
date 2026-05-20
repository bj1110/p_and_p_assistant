#include "resizingButton.hpp"

namespace graphics{

ResizingButton::ResizingButton(sf::Font& font, const std::string& text, sf::Vector2f pos, std::function<void()> callback)
: ButtonTemplate::ButtonTemplate(font, text, pos, callback){
    resize(); 
}


void ResizingButton::resize(){
    sf::FloatRect bounds= text_.getLocalBounds();
    shape_.setRectangleSize(bounds.getSize() + padding_);
    placeText(); 
}  

} //namespace graphics 