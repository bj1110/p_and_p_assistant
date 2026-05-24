#pragma once
#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "core/gameboard.hpp"
#include "core/settings.hpp"

namespace graphics
{

class SelectionMenu; 

struct SelectionMenuEntry{
    sf::Text text {};
    std::function<void(const sf::Event&, std::weak_ptr<SelectionMenu>, size_t)> callback {};
};

class SelectionMenu: public sf::Drawable, public std::enable_shared_from_this<SelectionMenu> {

public:
SelectionMenu(std::shared_ptr<core::Settings> settings, const std::vector<SelectionMenuEntry>& entries, sf::Vector2f position, sf::Vector2f size_per_element, sf::Vector2f margin); 

void handleEvent(const sf::Event& event);

void highlightSelection(size_t idx);

private:

void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
std::shared_ptr<core::Settings> settings_ = nullptr; 
std::vector<SelectionMenuEntry> entries_; 
sf::Vector2f position_ {}; 
sf::Vector2f size_per_element_ {}; 
sf::RectangleShape background_ {}; 
sf::Vector2f margin_ {}; 
};


} // namespace graphics
