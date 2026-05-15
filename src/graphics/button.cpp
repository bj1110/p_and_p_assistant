#include "button.hpp"
#include "utils/logger.hpp"


namespace graphics{


Button::Button(const std::string& text, sf::Vector2f pos){
    if (!font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        LOG_ERROR("Font not found"); 
    }
    text_.setFont(font_); 
    text_.setString(text);
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::White);
    shape_.setFillColor(sf::Color(149, 159, 92));

    setPosition(pos); 
}

void Button::setPosition(sf::Vector2f pos){
    shape_.setPosition(pos);
    sf::FloatRect bounds= text_.getLocalBounds();
    shape_.setRectangleSize(bounds.getSize() + sf::Vector2f{10.f, 20.f});
    text_.setOrigin(-sf::Vector2f{2.5f, 5.f}); 
    text_.setPosition(pos);
    std::string t = text_.getString();
    sf::FloatRect sb = shape_.getLocalBounds(); 
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(shape_);
    target.draw(text_); 
}

void Button::setString(const std::string& str){
    text_.setString(str);
    setPosition(shape_.getPosition()); 
}

void Button::setButtonColor(sf::Color color){
    shape_.setFillColor(color);
}

void Button::setTextColor(sf::Color color){
    text_.setFillColor(color); 
}

} //namespace graphics