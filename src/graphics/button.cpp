#include "button.hpp"
#include "utils/logger.hpp"


namespace graphics{


Button::Button(const std::string& text){
    if (!font_.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        LOG_ERROR("Font not found"); 
    }
    text_.setFont(font_); 
    text_.setString(text);
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::White);
    text_.setPosition(pos_.x + 15.f, pos_.y + 15.f);
    shape_.setRectangleSize({50.f, 50.f}); 
    shape_.setPosition(pos_); 
    shape_.setFillColor(sf::Color(149, 159, 92));

    sf::FloatRect bounds= text_.getGlobalBounds();
    sf::FloatRect boxbounds = shape_.getGlobalBounds(); 

    LOG_INFO(std::format("Box bounds pos ({},{}) and size ({}, {})", boxbounds.getPosition().x, boxbounds.getPosition().y, boxbounds.getSize().x, boxbounds.getSize().y)); 

    LOG_INFO(std::format("Text bounds pos ({},{}) and size ({}, {})", bounds.getPosition().x, bounds.getPosition().y, bounds.getSize().x, bounds.getSize().y)); 

}

void Button::setPosition(sf::Vector2f pos){
    pos_ = pos;
    shape_.setPosition(pos_);
    text_.setPosition(pos_.x + 5.f, pos_.y + 5.f); 

    
    sf::FloatRect bounds= text_.getGlobalBounds();
    shape_.setRectangleSize( {bounds.getPosition().x* 0.4f, bounds.getPosition().y*0.2f});

    sf::Vector2f shape_size = shape_.getGlobalBounds().getSize();
    sf::Vector2f textpos = shape_.getPosition() + sf::Vector2f{shape_size.x/4.f , shape_size.y/4.f} ; 
    text_.setPosition(textpos);
    
    sf::FloatRect boxbounds = shape_.getGlobalBounds(); 

    auto text_pos = text_.getPosition();

    LOG_INFO(std::format("Box bounds pos ({},{}) and size ({}, {})", boxbounds.getPosition().x, boxbounds.getPosition().y, boxbounds.getSize().x, boxbounds.getSize().y)); 

    LOG_INFO(std::format("Text bounds pos ({},{}) and size ({}, {})", bounds.getPosition().x, bounds.getPosition().y, bounds.getSize().x, bounds.getSize().y)); 
    LOG_INFO(std::format("Text pos: ({}, {})", text_pos.x, text_pos.y)); 
}


void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(shape_);
    target.draw(text_); 
}


} //namespace graphics