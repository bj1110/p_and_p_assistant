#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include "gameboard/gameboard.hpp"
#include <SFML/Graphics.hpp>
#include "graphics/text.hpp"
#include "graphics/buttonShape.hpp"
#include "graphics/button.hpp"

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pen and Paper Assistant");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    graphics::Text text {};
    
    gameboard::Gameboard gameboard{};
    gameboard.init(2, {2, 8, 10, 20, 100});
    
    utils::Logger::get_logger().changeLogLevel(utils::Debug); 

    graphics::ButtonShape button { {70.f, 30.f}};
    button.setPosition(300.f, 300.f); 
    button.setFillColor(sf::Color::Green);

    const std::string msg = "hallpo";
    graphics::Button btn(msg);
    btn.setPosition({100.f, 100.f}); 


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }
            if(event.type==sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Space){
                    int rnd = gameboard.roll_dice(20);
                    text.setText(std::format("you rolled: {}", rnd));
                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(text.getText());
        window.draw(button); 
        window.draw(btn); 
        window.display(); 
    }

    return 0;
}