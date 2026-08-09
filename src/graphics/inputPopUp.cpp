#include "inputPopUp.hpp"
#include "GUI_manager.hpp"

namespace graphics{


InputPopUp::InputPopUp(std::shared_ptr<core::Settings> settings, sf::Vector2f size, std::string title, const std::vector<std::string>& fields):
m_settings(settings)
{
    m_shape.setRectangleSize(size);
    m_shape.setCornerSharpeness(50.f);
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
    sf::Vector2f cb_pos {
        windowCenter.x +  size.x / 2.7f ,
        windowCenter.y - size.y/ 2.1f  
        };
    m_closeButton = std::make_unique<ResizingButton> (settings->font,"X", cb_pos, [this](ButtonTemplate&){this->close();} );
    m_closeButton->setButtonColor(sf::Color{100, 100, 100, 70});
    sf::Vector2f fieldSize{
        size.x - 40.f,
        30.f
    };

    const float spacing = 15.f;
    const float labelSpacing = 5.f;

    float y = windowCenter.y - size.y / 2.f + 60.f;

    for (const std::string& str : fields)
    {
        sf::Vector2f fieldPosition{
            windowCenter.x - fieldSize.x / 2.f,
            y
        };

        Textfield f{
            fieldSize,
            fieldPosition,
            m_settings
        };

        sf::Text t{
            sf::String{str},
            m_settings->font
        };

        t.setCharacterSize(10);
        t.setFillColor(sf::Color::Black);

        auto bounds = t.getLocalBounds();

        t.setPosition(
            fieldPosition.x,
            fieldPosition.y - bounds.height - labelSpacing
        );

        m_fields.emplace_back(t, f);

        y += fieldSize.y + bounds.height + spacing + labelSpacing;
    }

    
}

void InputPopUp::close(){
    if(auto tmp= manager.lock()){
        if (!tmp ->removeElement(this)){
            LOG_ERROR("Couldn't close");
        }
    }
}

void InputPopUp::handleEvent(const sf::Event& event){
    m_closeButton->handleEvent(event);
    for(auto& field:m_fields){
        field.second.handleEvent(event);
    }
}

void InputPopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(auto tmp = manager.lock()){
        tmp->focusElement(this);
    }
    target.draw(m_shape);
    target.draw(m_title);
    target.draw(*m_closeButton);
    for(const auto& field: m_fields){
        target.draw(field.first);
        target.draw(field.second);
    }
}

} // namespace graphics