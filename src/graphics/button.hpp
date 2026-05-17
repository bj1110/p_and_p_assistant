#pragma once
#include "buttonShape.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include "utils/logger.hpp"

namespace graphics{

class Button: public sf::Drawable{
public:    
    Button(const std::string& text, sf::Vector2f pos = {0.f, 0.f}, std::function<void()> callback = [](){LOG_ERROR("No callback set");});

    void setPosition(sf::Vector2f pos);

    void setString(const std::string& str);
    void setButtonColor(sf::Color color);
    void setTextColor(sf::Color color); 

    void isClicked(const sf::Event::MouseButtonEvent& event) const; 
    void setCallback(std::function<void()> callback); 

private:
void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 

ButtonShape shape_ {};
sf::Font font_ {}; 
sf::Text text_ {};
std::function<void()> callback_; 
}; 

} //namespace graphics