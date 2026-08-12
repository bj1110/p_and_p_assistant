#include "inputPopUp.hpp"
#include "GUI_manager.hpp"

namespace graphics{


InputPopUp::InputPopUp(std::shared_ptr<core::Settings> settings, sf::Vector2f size, std::string title, const std::vector<InputType>& fields, SubmitCallback on_submit):
m_settings(settings), m_onsubmit(on_submit)
{
    constexpr float padding = 15.f; 

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

    auto title_bounds = m_title.getLocalBounds();
    m_title.setOrigin(
        title_bounds.getPosition().x + title_bounds.getSize().x / 2.f,
        title_bounds.getPosition().y + title_bounds.getSize().y /2.f 
    );

    m_title.setPosition(
        windowCenter.x ,
        windowCenter.y - size.y/2.f + title_bounds.getSize().y/2.f + padding
    );

    const float spacing = 15.f;
    const float labelSpacing = 5.f;


    m_closeButton = std::make_unique<ResizingButton> (settings->font,"X", sf::Vector2f{0.f, 0.f}, [this](ButtonTemplate&){this->close();} );
    m_closeButton->setButtonColor(sf::Color{100, 100, 100, 70});
    m_closeButton->setCharacterSize(10); 
    m_closeButton->setShapesCornerSharpeness(6.f);

    auto shape_bounds = m_shape.getLocalBounds();
    auto cb_bounds = m_closeButton->getLocalBounds();
    m_closeButton->setOrigin(
        cb_bounds.getPosition().x + cb_bounds.getSize().x / 2.f,
        cb_bounds.getPosition().y + cb_bounds.getSize().y / 2.f
    );
    m_closeButton->setPosition({
        windowCenter.x + size.x / 2.f
            - padding
            - cb_bounds.getSize().x / 2.f,

        windowCenter.y - size.y / 2.f
            + padding
            + cb_bounds.getSize().y / 2.f
    });


    m_submit = std::make_unique<ResizingButton>(settings->font, "Submit",  sf::Vector2f{0.f, 0.f}, [this](ButtonTemplate&){submit();});
    m_submit->setButtonColor(sf::Color{100, 100, 100, 70});


    auto submit_bounds = m_submit->getLocalBounds();
    m_submit->setOrigin(
        submit_bounds.getPosition().x + submit_bounds.getSize().x / 2.f,
        submit_bounds.getPosition().y + submit_bounds.getSize().y / 2.f
    );
    m_submit->setPosition({
        windowCenter.x + size.x / 2.f
            - padding
            - submit_bounds.getSize().x / 2.f,

        windowCenter.y + size.y / 2.f
            - padding
            - submit_bounds.getSize().y / 2.f
    });


    sf::Vector2f fieldSize{
        size.x - 40.f,
        30.f
    };



    float y = windowCenter.y - size.y / 2.f + 60.f;

    for (const InputType& field : fields)
    {
        sf::Vector2f fieldPosition{
            windowCenter.x - fieldSize.x / 2.f,
            y
        };

        Textfield f{
            fieldSize,
            fieldPosition,
            m_settings,
            field.type
        };

        sf::Text t{
            sf::String{field.fieldname},
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
        tmp->focusAll();
        if (!tmp ->removeElement(this)){
            LOG_ERROR("Couldn't close");
        }
    }
}

void InputPopUp::handleEvent(const sf::Event& event){
    m_closeButton->handleEvent(event);
    for(auto& field:m_fields){
        field.field.handleEvent(event);
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab){
        LOG_INFO("Tab pressed");
        for(int i=0; i<m_fields.size(); ++i){
            auto& field = m_fields[i];
            if(field.field.is_selected()){
                LOG_INFO(std::format("{} selected", i));
                field.field.unselect();
                if(i!=m_fields.size()-1){
                    m_fields[i+1].field.select();
                }
                break;
            }
        }
    }
    m_submit->handleEvent(event);
}

void InputPopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    if(auto tmp = manager.lock()){
        tmp->focusElement(this);
    }
    target.draw(m_shape, states);
    target.draw(m_title, states);
    target.draw(*m_closeButton, states);
    for(const auto& field: m_fields){
        target.draw(field.fieldname, states);
        target.draw(field.field, states);
    }
    target.draw(*m_submit, states);
}


void InputPopUp::submit(){
    InputResult result;
    for(const auto& [name, field, type]: m_fields){
        result[name.getString()] = field.getValue();
    }
    if(m_onsubmit){
        m_onsubmit(result);
    } else{
        LOG_ERROR("No submit callback supplied. Data from this input field is lost.");
    }
    close();
}

} // namespace graphics