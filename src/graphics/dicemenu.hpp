#pragma once
#include <vector>
#include "components/fixedSizeButton.hpp"
#include "components/resizingButton.hpp"
#include <mechanics/dice.hpp>
#include <core/gameboard.hpp>
#include <core/settings.hpp>

namespace graphics
{

class DiceMenu : public sf::Drawable{
public:

    DiceMenu(std::shared_ptr<core::Settings> settings, std::shared_ptr<core::Gameboard> gameboard, sf::Vector2f btn_size, sf::Vector2f margin);

    void handleEvent(const sf::Event& event); 


private: 
    std::function<void()> createButtonLambda(u_int sides) const; 
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
    std::vector<std::unique_ptr<FixedSizeButton>> buttons_ {}; 
    sf::Vector2f button_sizes_ {};
    std::shared_ptr<core::Settings> settings_ {}; 
    std::shared_ptr<core::Gameboard> gameboard_ {}; 
    std::unique_ptr<ResizingButton> expandButton_ {}; 
    std::unique_ptr<FixedSizeButton> result_button_ {}; 
    bool hide_menu_ = true;

};

} // namespace graphics
