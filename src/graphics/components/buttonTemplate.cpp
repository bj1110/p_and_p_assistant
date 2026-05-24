#include "buttonTemplate.hpp"


namespace graphics{


ButtonTemplate::ButtonTemplate(const sf::Font& font, const std::string& text, sf::Vector2f pos, std::function<void()> callback ):
callback_(callback)
{
    text_.setFont(font); 
    text_.setString(text);
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::White);
    shape_.setFillColor(default_button_color_);
    setPosition(pos); 
}

void ButtonTemplate::setCallback(std::function<void()> callback){
    callback_= callback; 
}

void ButtonTemplate::setPosition(sf::Vector2f pos){
    shape_.setPosition(pos);
    placeText(); 
}


void ButtonTemplate::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(shape_);
    target.draw(text_); 
}

void ButtonTemplate::setString(const std::string& str){
    text_.setString(str);
    resize(); 
}

void ButtonTemplate::setButtonColor(sf::Color color){
    shape_.setFillColor(color);
    default_button_color_ = color; 
}

void ButtonTemplate::setTextColor(sf::Color color){
    text_.setFillColor(color); 
}


void ButtonTemplate::handleMouseClick(const sf::Event::MouseButtonEvent& event) const{
    if(event.button != sf::Mouse::Button::Left){
        return;
    }
    if(isMouseOnButton(event.x, event.y)){
        LOG_DEBUG("Mouse clicked on Button");
        callback_(); 
    }
}

void ButtonTemplate::onMouseHover(const sf::Event::MouseMoveEvent& event){
    if(isMouseOnButton(event.x, event.y)){
        sf::Color currColor = shape_.getFillColor();
        shape_.setFillColor(default_button_color_ + sf::Color{30, 30, 30});
    }
    else{
        shape_.setFillColor(default_button_color_); 
    }
}

bool ButtonTemplate::isMouseOnButton(const float x, const float y) const{
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

void ButtonTemplate::handleEvent(const sf::Event& event){
    if(event.type == sf::Event::MouseButtonPressed){
        handleMouseClick(event.mouseButton);
    }
    if(event.type == sf::Event::MouseMoved){
        onMouseHover(event.mouseMove);
    }
}

const sf::Vector2f ButtonTemplate::getSize()const{
    return shape_.getLocalBounds().getSize();
}

void ButtonTemplate::placeText(){
    sf::FloatRect text_bounds = text_.getLocalBounds(); 

    text_.setOrigin({
        text_bounds.getPosition().x + text_bounds.getSize().x / 2.f,
        text_bounds.getPosition().y + text_bounds.getSize().y / 2.f
    });
   
    sf::FloatRect shape_bounds = shape_.getGlobalBounds();

    text_.setPosition({
        shape_bounds.getPosition().x + shape_bounds.getSize().x / 2.f,
        shape_bounds.getPosition().y + shape_bounds.getSize().y / 2.f
    });
}

void ButtonTemplate::setShapesCornerSharpeness(float sharpeness){
    shape_.setCornerSharpeness(sharpeness);
}

} //namespace graphics