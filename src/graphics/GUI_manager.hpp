#pragma once
#include <vector>
#include <memory>
#include "graphics/GUI_element.hpp"
#include <SFML/Graphics.hpp>
#include "utils/logger.hpp"



namespace graphics{


class GUI_manager: public std::enable_shared_from_this<GUI_manager>{

public:
    GUI_manager() = default;

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window) const ; 
    void focusElement(const GUI_element* element);
    void focusAll();


    [[nodiscard]] bool addElement(std::shared_ptr<GUI_element> element);
    [[nodiscard]] bool removeElement(GUI_element* element);

    void update();


private:
    std::vector<std::shared_ptr<GUI_element>> gui_elements {};
    std::vector<GUI_element*> m_deletion {};


};



    
} // namespace graphics
