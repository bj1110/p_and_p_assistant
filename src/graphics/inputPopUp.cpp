#include "inputPopUp.hpp"
#include "GUI_manager.hpp"

namespace graphics{


InputPopUp::InputPopUp(std::shared_ptr<core::Settings> settings, sf::Vector2f size, std::string title, std::vector<std::string> fields):
m_settings(settings), m_fields(std::move(fields))
{
    m_shape.setRectangleSize(size);
    m_title.setFont(settings->font);
    m_title.setString(title);
    m_title.setStyle(sf::Text::Bold);
    m_title.setCharacterSize(20);
    m_title.setFillColor(sf::Color::Black);
    sf::Vector2f windowCenter{
        settings->windowsize.x / 2.f,
        settings->windowsize.y / 2.f
    };

    m_shape.setRectangleSize(size);
    m_shape.setOrigin(size.x / 2.f, size.y / 2.f);
    m_shape.setPosition(windowCenter);

    auto bounds = m_title.getLocalBounds();
    m_title.setOrigin(
        bounds.getPosition().x + bounds.getSize().x / 2.f,
        bounds.getPosition().y
    );

    m_title.setPosition(
        windowCenter.x,
        windowCenter.y - size.y / 2.f + 15.f
    );
}


void InputPopUp::handleEvent(const sf::Event& event){
    if(event.type == sf::Event::TextEntered){
        LOG_INFO("input popup event handler called"); 

    }
}

void InputPopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(auto tmp = manager.lock()){
        tmp->focusElement(this);
    }
    target.draw(m_shape);
    target.draw(m_title);
}

} // namespace graphics