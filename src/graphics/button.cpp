#include "button.hpp"


namespace graphics{


Button::Button(sf::Font& font, const std::string& text, sf::Vector2f pos, std::function<void()> callback ):
callback_(callback)
{
    text_.setFont(font); 
    text_.setString(text);
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::White);
    shape_.setFillColor(default_button_color_);

    setPosition(pos); 
}

void Button::setCallback(std::function<void()> callback){
    callback_= callback; 
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
    default_button_color_ = color; 
}

void Button::setTextColor(sf::Color color){
    text_.setFillColor(color); 
}


void Button::handleMouseClick(const sf::Event::MouseButtonEvent& event) const{
    if(event.button != sf::Mouse::Button::Left){
        return;
    }
    if(isMouseOnButton(event.x, event.y)){
        LOG_DEBUG("Mouse clicked on Button");
        callback_(); 
    }
}

void Button::onMouseHover(const sf::Event::MouseMoveEvent& event){
    if(isMouseOnButton(event.x, event.y)){
        sf::Color currColor = shape_.getFillColor();
        shape_.setFillColor(default_button_color_ + sf::Color{30, 30, 30});
    }
    else{
        shape_.setFillColor(default_button_color_); 
    }
}

bool Button::isMouseOnButton(const float x, const float y) const{
    const sf::FloatRect buttonBounds = shape_.getGlobalBounds();
    const sf::Vector2f& buttonPos = buttonBounds.getPosition();
    const sf::Vector2f& buttonSize = buttonBounds.getSize();
    if(x < buttonPos.x || x > buttonPos.x + buttonSize.x){
        return false;
    }
    if(y < buttonPos.y || y > buttonPos.y + buttonSize.y){
        return false;
    }
    return true; 
}

} //namespace graphics