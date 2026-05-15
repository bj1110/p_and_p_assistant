#pragma once
#include "buttonShape.hpp"
#include <SFML/Graphics.hpp>

namespace graphics{

class Button: public sf::Drawable{
public:    
    Button(const std::string& text, sf::Vector2f pos = {0.f, 0.f});

    void setPosition(sf::Vector2f pos);

private:
void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 

ButtonShape shape_ {};
sf::Font font_ {}; 
sf::Text text_ {};
}; 

} //namespace graphics