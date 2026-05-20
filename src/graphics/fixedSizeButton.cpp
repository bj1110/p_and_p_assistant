#include "fixedSizeButton.hpp"

namespace graphics
{
    
FixedSizeButton::FixedSizeButton(sf::Font& font, const std::string& text, sf::Vector2f pos, sf::Vector2f size, std::function<void()> callback)
:ButtonTemplate(font, text, pos, callback), size_(size){
    resize();
}

void FixedSizeButton::resize(){
    shape_.setRectangleSize(size_);
    text_.setScale(1.f, 1.f); 

    sf::Vector2f text_size = text_.getLocalBounds().getSize(); 

    sf::Vector2f target_size= size_ - padding_; 

    u_int curr_char_size = text_.getCharacterSize();

    if(text_size.x <= 0.f || text_size.y <= 0.f){
        return;
    }

    float factor = std::min(target_size.x/ text_size.x, target_size.y/text_size.y);

    text_.setScale({factor, factor});
    placeText(); 
}

void FixedSizeButton::setSize(float x, float y){
    size_={x, y};
    resize(); 
}


} // namespace graphics
