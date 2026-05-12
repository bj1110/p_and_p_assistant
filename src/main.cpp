#include <iostream>
#include "entities/warrior.hpp"
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include "gameboard/gameboard.hpp"
#include <SFML/Graphics.hpp>
#include "graphics/text.hpp"

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Flap");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    graphics::Text text {};
    
    gameboard::Gameboard gameboard{};
    gameboard.init(2, {2, 8, 10, 20, 100});
    
    utils::Logger::get_logger().changeLogLevel(utils::Debug); 

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
        window.display(); 
    }

    return 0;
}