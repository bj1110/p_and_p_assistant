#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include "gameboard/gameboard.hpp"
#include <SFML/Graphics.hpp>
#include "graphics/buttonShape.hpp"
#include "graphics/button.hpp"

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pen and Paper Assistant");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);
    
    gameboard::Gameboard gameboard{};
    gameboard.init(2, {2, 8, 10, 20, 100});
    
    CHANGE_LOG_LEVEL(utils::Debug); 

    int w20_int = 20; 
    graphics::Button w20("Click to Roll W20", {50.f, 50.f}, [&gameboard, &w20, &w20_int](){
        int rnd = gameboard.roll_dice(w20_int);
        w20.setString(std::format("you rolled: {}", rnd));
    });


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }
            if(event.type== sf::Event::MouseButtonPressed){
                w20.isClicked(event.mouseButton); 
            }
            if(event.type== sf::Event::MouseMoved){
                w20.hover(event.mouseMove);
            }
        }
        window.clear(sf::Color::Black);
        window.draw(w20);
        window.display(); 
    }

    return 0;
}