#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include "gameboard/gameboard.hpp"
#include <SFML/Graphics.hpp>
#include "graphics/resizingButton.hpp"

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pen and Paper Assistant");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    
    gameboard::Gameboard gameboard{};
    gameboard.init(2, {2, 8, 10, 20, 100});

    //TODO: localize font in project 
    sf::Font font {};
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        LOG_ERROR("Font not found"); 
    }

    int w20_int = 20; 
    graphics::resizingButton w20(font, "Click to Roll W20", {50.f, 50.f}, [&gameboard, &w20, &w20_int](){
        int rnd = gameboard.roll_dice(w20_int);
        w20.setString(std::format("you rolled: {}", rnd));
    });


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }
            w20.handleEvent(event); 
        }
        window.clear(sf::Color::Black);
        window.draw(w20);
        window.display(); 
    }

    return 0;
}