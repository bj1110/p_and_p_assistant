#include "text.hpp"
#include "utils/logger.hpp"

namespace graphics{

Text::Text(){
    if (!font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        LOG_ERROR("Font not found"); 
    }
    text_.setFont(font_); 
    text_.setCharacterSize(40);
    text_.setFillColor(sf::Color::Red);
    text_.setPosition(100.f, 100.f);
}

void Text::setText(const std::string& text){
    text_.setString(text); 
}

sf::Text& Text::getText(){
    return text_; 
}

void Text::setCharacterSize(int size){
    text_.setCharacterSize(size);
}
void Text::setColor(const sf::Color& color){
    text_.setFillColor(color);
}
void Text::setPosition(float x, float y){
    text_.setPosition(x, y);
}

} //namespace graphics