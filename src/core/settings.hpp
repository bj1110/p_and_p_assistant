#pragma once
#include  <SFML/Graphics.hpp>

namespace core
{

/**
 * Struct that holds different settings needed around the game 
 * 
 * @var Settings::windowsize    Size of the window
 * @var Settings::font          sf::Font used around the Project
 */
struct Settings{
    sf::Vector2u windowsize {}; 
    sf::Font font {}; 
};
} // namespace gameboard
