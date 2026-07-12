#pragma once    
#include "components/buttonShape.hpp"
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include "GUI_element.hpp"
#include "core/settings.hpp"
#include "utils/logger.hpp"



namespace graphics{

class InputPopUp : public GUI_element{

public: 
    InputPopUp(std::shared_ptr<core::Settings> settings, sf::Vector2f size, std::string title, std::vector<std::string> fields);


    void handleEvent(const sf::Event& event) override;


private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 

private:
    std::shared_ptr<core::Settings> m_settings = nullptr; 
    ButtonShape m_shape {};
    sf::Text m_title {}; 
    std::vector<std::string> m_fields {};

};




} // namespace graphics