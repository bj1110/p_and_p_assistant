#pragma once
#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "core/gameboard.hpp"
#include "core/settings.hpp"

namespace graphics
{

class SelectionMenu: public sf::Drawable {

public:
SelectionMenu(std::shared_ptr<core::Settings> settings, const std::vector<std::string>& descriptors, const std::vector<std::function<void()>>& callbacks , sf::Vector2f position, sf::Vector2f size_per_element); 



private:

void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
std::shared_ptr<core::Settings> settings_ = nullptr; 
std::vector<std::string> descriptors_ {};
std::vector<std::function<void()>> callbacks_ {}; 
sf::Vector2f position_ {}; 
sf::Vector2f size_per_element_ {}; 
std::vector<sf::Text> texts_ {}; 
sf::RectangleShape background_ {}; 

};


} // namespace graphics
