#pragma once
#include "buttonShape.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include "utils/logger.hpp"

namespace graphics{

class ButtonTemplate: public sf::Drawable{
public:    
    using ButtonCallback = std::function<void(ButtonTemplate&)>;
    ButtonTemplate(const sf::Font& font, const std::string& text, sf::Vector2f pos = {0.f, 0.f}, ButtonCallback callback = [](ButtonTemplate&){LOG_ERROR("No callback set");});

    virtual ~ButtonTemplate() = default; 

    virtual void resize() =0; 

    virtual void setPosition(sf::Vector2f pos);

    void setString(const std::string& str);
    void setButtonColor(sf::Color color);
    void setTextColor(sf::Color color); 

    void handleMouseClick(const sf::Event::MouseButtonEvent& event); 
    void setCallback(ButtonCallback callback); 
    void onMouseHover(const sf::Event::MouseMoveEvent& event);

    void handleEvent(const sf::Event& event);

    const sf::Vector2f getSize()const;

    void setShapesCornerSharpeness(float sharpeness);

    sf::Color getButtonColor()const;

protected:
void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
bool isMouseOnButton(const float x, const float y) const; 
void placeText();

ButtonShape shape_ {}; 
sf::Text text_ {};
ButtonCallback callback_ {}; 
sf::Color default_button_color_ = sf::Color(150, 160, 90);
sf::Vector2f padding_ {10.f, 20.f}; 
}; 

} //namespace graphics