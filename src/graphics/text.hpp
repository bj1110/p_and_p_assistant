#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace graphics{

class Text{
    public:
    Text();

    void setText(const std::string& text);

    sf::Text& getText();
    void setColor(const sf::Color& color);
    void setCharacterSize(int size);
    void setPosition(float x, float y);
    


private:
    sf::Font font_ {};
    sf::Text text_ {}; 
};


} //namespace graphics