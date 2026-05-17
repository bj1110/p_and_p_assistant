#include "button.hpp"


namespace graphics{


Button::Button(const std::string& text, sf::Vector2f pos, std::function<void()> callback):
callback_(callback)
{
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
}

void Button::setTextColor(sf::Color color){
    text_.setFillColor(color); 
}


void Button::isClicked(const sf::Event::MouseButtonEvent& event) const{
    const sf::FloatRect buttonBounds = shape_.getGlobalBounds();
    const sf::Vector2f& buttonPos = buttonBounds.getPosition();
    const sf::Vector2f& buttonSize = buttonBounds.getSize();
    if(event.button != sf::Mouse::Button::Left){
        return;
    }
    if(event.x > buttonPos.x && event.x < buttonPos.x + buttonSize.x){
        if(event.y > buttonPos.y && event.y < buttonPos.y + buttonSize.y){
            LOG_DEBUG("Mouse clicked on Button");
            callback_(); 
        }
    }
}

} //namespace graphics