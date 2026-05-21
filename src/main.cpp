#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include "gameboard/gameboard.hpp"
#include <SFML/Graphics.hpp>
#include "graphics/dicemenu.hpp"

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pen and Paper Assistant");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    
    std::shared_ptr<gameboard::Gameboard> gameboard = std::make_shared<gameboard::Gameboard>();
    gameboard->init(2, {2, 8, 10, 20, 100});

    //TODO: localize font in project 
    sf::Font font {};
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        LOG_ERROR("Font not found"); 
    }

    graphics::DiceMenu dicemenu {font, gameboard, {150.f, 50.f}, {10.f, 10.f}}; 
    


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }
            dicemenu.handleEvent(event); 
        }
        window.clear(sf::Color::Black);
        window.draw(dicemenu); 
        window.display(); 
    }

    return 0;
}