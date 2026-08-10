#pragma once

#include "SFML/Graphics.hpp"
#include "graphics/GUI_element.hpp"
#include "utils/logger.hpp"
#include "buttonShape.hpp"
#include "core/settings.hpp"
#include <variant>
#include <string>

namespace graphics
{


class Textfield : public GUI_element{

public:
enum class Type {String, Int};

public:
    Textfield(sf::Vector2f size, sf::Vector2f position, std::shared_ptr<core::Settings> settings, Type type = Type::String)
    : m_shape(size), m_settings(settings), m_type(type){
        m_shape.setPosition(position);
        m_text.setFont(m_settings->font);
        m_text.setFillColor(sf::Color::Black);
        m_text.setPosition(position);
        m_text.setCharacterSize(20);
        m_shape.setFillColor(sf::Color::White);
        m_shape.setOutlineColor(sf::Color::Black);
        m_shape.setOutlineThickness(3.f);
        m_shape.setCornerSharpeness(50.f);
    }

    void handleEvent(const sf::Event& event){
        if(event.type == sf::Event::MouseButtonPressed){
            float x = event.mouseButton.x, y = event.mouseButton.y; 
            const sf::FloatRect bounds = m_shape.getGlobalBounds();
            const sf::Vector2f& pos = bounds.getPosition();
            const sf::Vector2f& size = bounds.getSize();
            if(x < pos.x || x > pos.x + size.x){
                isSelected=false;
                return;
            }
            if(y < pos.y || y > pos.y + size.y){
                isSelected=false;
                return;
            }
            isSelected = true; 
        }
        if(!isSelected){
            return;
        }
        if(event.type == sf::Event::TextEntered){
            sf::Uint32 code = event.text.unicode;
            if(m_type== Type::String && code>=32){
                m_text.setString(m_text.getString()+ code);
            }
            else if(m_type== Type::Int && code>='0' && code <='9'){
                m_text.setString(m_text.getString() + code);
            }
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Backspace){
            sf::String str = m_text.getString();
            if(!str.isEmpty()){
                str.erase(str.getSize()-1, 1);
            }
            m_text.setString(str);
        }
    }

    sf::String getString()const{
        return m_text.getString();
    }

    std::variant<std::string, int> getValue()const{
        sf::String str = getString();
        if(m_type== Type::String){
            return str;
        }
        if(str.isEmpty()){
            return -1;
        }
        return std::stoi(str.toAnsiString());
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
        target.draw(m_shape);
        target.draw(m_text);
    }




private:

ButtonShape m_shape{};
sf::Text m_text {};
std::shared_ptr<core::Settings> m_settings{};
bool isSelected = false;
Type m_type = Type::String;


};


    
} // namespace graphics
