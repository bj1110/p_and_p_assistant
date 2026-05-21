#pragma once
#include <vector>
#include "components/fixedSizeButton.hpp"
#include "components/resizingButton.hpp"
#include <mechanics/dice.hpp>
#include <gameboard/gameboard.hpp>

namespace graphics
{

class DiceMenu : public sf::Drawable{
public:

    DiceMenu(const sf::Font& font, std::shared_ptr<gameboard::Gameboard> gameboard, sf::Vector2f btn_size, sf::Vector2f margin);

    void handleEvent(const sf::Event& event); 


private: 
    std::function<void()> createButtonLambda(FixedSizeButton* btn, u_int sides) const; 
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
    std::vector<std::unique_ptr<FixedSizeButton>> buttons_ {}; 
    sf::Vector2f button_sizes_ {};
    std::shared_ptr<gameboard::Gameboard> gameboard_ {}; 
    ResizingButton expandButton_; 
    bool hide_menu_ = true;

};

} // namespace graphics
