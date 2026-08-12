#include "graphics/GUI_manager.hpp"
#include <cassert>

namespace graphics
{


    
void GUI_manager::handleEvent(const sf::Event& event){
    for(const auto& elem: gui_elements){
        if(elem->isFocussed()){
            elem->handleEvent(event);
        }
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

bool GUI_manager::removeElement(GUI_element* element){
    if(element==nullptr){
        return false;
    }
    m_deletion.push_back(element); 
    return true; 
}

void GUI_manager::update(){
    if(!m_deletion.empty()){
        for(GUI_element* el: m_deletion){
            for(auto it= gui_elements.begin(); it != gui_elements.end(); ){
                if(it->get() == el){
                    it= gui_elements.erase(it);
                }
                else{
                    ++it;
                }
            }
        }
        focusAll(); 
    }
    m_deletion.clear(); 
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
