#pragma once
#include "buttonTemplate.hpp"

namespace graphics
{
    
class ResizingButton : public ButtonTemplate{

public: 

    using ButtonTemplate::ButtonTemplate; 

    ResizingButton (const sf::Font& font, const std::string& text, sf::Vector2f pos = {0.f, 0.f}, std::function<void()> callback = [](){LOG_ERROR("No callback set");}); 

    virtual void resize() override; 

};


} // namespace graphics
