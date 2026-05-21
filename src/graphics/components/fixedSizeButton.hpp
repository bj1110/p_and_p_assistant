#pragma once

#include "buttonTemplate.hpp"

namespace graphics
{

class FixedSizeButton : public ButtonTemplate{
public:
    using ButtonTemplate::ButtonTemplate;

    FixedSizeButton (const sf::Font& font, const std::string& text, sf::Vector2f pos = {0.f, 0.f}, sf::Vector2f size ={100.f, 100.f}, std::function<void()> callback = [](){LOG_ERROR("No callback set");}); 

    
    virtual void resize() override;
    void setSize(float x, float y); 

private:

    sf::Vector2f size_ = {100.f, 100.f}; 

};
    
} // namespace graphics

