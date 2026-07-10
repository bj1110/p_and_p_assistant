#pragma once
#include <vector>
#include <string>
#include <functional>
#include "graphics/GUI_element.hpp"
#include "core/gameboard.hpp"
#include "core/settings.hpp"
#include "components/fixedSizeButton.hpp"

namespace graphics
{

class SelectionMenu; 
using SelectionMenuCallback = std::function<void(const sf::Event&, std::weak_ptr<SelectionMenu>, size_t)>;

struct SelectionMenuItem{
    std::string text {};
    SelectionMenuCallback callback {};
};


class SelectionMenu: public graphics::GUI_element, public std::enable_shared_from_this<SelectionMenu> {

public:
    SelectionMenu(std::shared_ptr<core::Settings> settings, const std::vector<std::string>& items, sf::Vector2f position, sf::Vector2f size_per_element, sf::Vector2f margin); 

    void handleEvent(const sf::Event& event);

    void highlightSelection(size_t idx);


private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ButtonTemplate::ButtonCallback createSelectionLambda(); 
    void expandOptions();

    private:
    std::shared_ptr<core::Settings> settings_ = nullptr; 
    std::vector<std::unique_ptr<FixedSizeButton>> buttons_ {}; 
    std::unique_ptr<FixedSizeButton> base_button_ {}; 
    std::unique_ptr<FixedSizeButton> expand_button_ {}; 
    sf::Vector2f position_ {}; 
    sf::Vector2f size_per_element_ {};
    sf::Vector2f margin_ {}; 
    ButtonTemplate* selected_ {};
    bool options_hidden_ = true; 
};
} // namespace graphics
