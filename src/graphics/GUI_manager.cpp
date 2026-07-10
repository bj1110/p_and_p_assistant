#include "graphics/GUI_manager.hpp"
#include <cassert>

namespace graphics
{


    
void GUI_manager::handleEvent(const sf::Event& event){
    for(const auto& elem: gui_elements){
        elem->handleEvent(event);
    }
}

void GUI_manager::draw(sf::RenderWindow& window)const{
    for(const auto& elem: gui_elements){
        window.draw(*elem);
    }
}

bool GUI_manager::addElement(std::shared_ptr<GUI_element> element){
    if(element == nullptr){
        return false;
    }
    element->registerElement(this->weak_from_this());
    gui_elements.push_back(std::move(element));
    return true;
}

void GUI_manager::focusElement(const GUI_element* element){
    if(element==nullptr){
        focusAll();
        return;
    }
    for(const auto& elem: gui_elements){
        if(elem.get() == element){
            elem->focusElement();
        }
        else{
            elem->unfocusElement();
        }
    }
}

void GUI_manager::focusAll(){
    for(const auto& elem:gui_elements){
        elem->focusElement();
    }
}

} // namespace graphics
