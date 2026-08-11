#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace graphics
{

class GUI_manager;

class GUI_element: public sf::Drawable, public sf::Transformable{
public:
    virtual  void handleEvent(const sf::Event& event) =0;
    virtual ~GUI_element() = default;

    inline bool isFocussed(){return focus;}
    
    inline void focusElement(){focus= true;}
    inline void unfocusElement(){focus=false;}

    inline void registerElement(std::weak_ptr<GUI_manager> gui_manager){
        manager = std::move(gui_manager);
    }
    
    protected:
    std::weak_ptr<GUI_manager> manager; 

    
    private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override =0 ;
    
    
    bool focus = false;
};





} // namespace graphics