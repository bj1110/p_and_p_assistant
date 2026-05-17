#pragma once
#include "buttonShape.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include "utils/logger.hpp"

namespace graphics{

class Button: public sf::Drawable{
public:    
    Button(sf::Font& font, const std::string& text, sf::Vector2f pos = {0.f, 0.f}, std::function<void()> callback = [](){LOG_ERROR("No callback set");});

    void setPosition(sf::Vector2f pos);

    void setString(const std::string& str);
    void setButtonColor(sf::Color color);
    void setTextColor(sf::Color color); 

    void handleMouseClick(const sf::Event::MouseButtonEvent& event) const; 
    void setCallback(std::function<void()> callback); 
    void onMouseHover(const sf::Event::MouseMoveEvent& event);

    void handleEvent(const sf::Event& event);

private:
void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
bool isMouseOnButton(const float x, const float y) const; 

ButtonShape shape_ {}; 
sf::Text text_ {};
std::function<void()> callback_; 
sf::Color default_button_color_ = sf::Color(150, 160, 90);
}; 

} //namespace graphics