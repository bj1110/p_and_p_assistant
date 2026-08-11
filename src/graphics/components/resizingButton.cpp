#include "resizingButton.hpp"

namespace graphics{

ResizingButton::ResizingButton(const sf::Font& font, const std::string& text, sf::Vector2f pos, ButtonCallback callback)
: ButtonTemplate::ButtonTemplate(font, text, pos, callback){
    resize(); 
}


void ResizingButton::resize(){
    sf::FloatRect bounds= text_.getLocalBounds();
    shape_.setRectangleSize(bounds.getSize() + padding_);
    placeText(); 
}  

void ResizingButton::setCharacterSize(u_int size){
    text_.setCharacterSize(size);
    resize(); 
}

} //namespace graphics 