#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include "core/gameboard.hpp"
#include <SFML/Graphics.hpp>
#include "graphics/dicemenu.hpp"
#include "core/settings.hpp"

int main(){
    std::shared_ptr<core::Settings> settings = std::make_shared<core::Settings>(sf::Vector2u{800, 600});
    //TODO: localize font in project 
    if (!settings->font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        LOG_ERROR("Font not found"); 
    }

    sf::RenderWindow window(sf::VideoMode(settings->windowsize.x, settings->windowsize.y), "Pen and Paper Assistant");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    
    std::shared_ptr<core::Gameboard> gameboard = std::make_shared<core::Gameboard>();
    gameboard->init(2, {2, 8, 10, 20, 100});



    graphics::DiceMenu dicemenu {settings, gameboard, {150.f, 50.f}, {10.f, 10.f}}; 
    


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