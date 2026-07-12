#include <iostream>
#include "mechanics/dice.hpp"
#include "utils/logger.hpp"
#include <sstream>
#include "core/gameboard.hpp"
#include <SFML/Graphics.hpp>
#include "graphics/dicemenu.hpp"
#include "core/settings.hpp"
#include "graphics/selectionmenu.hpp"
#include "graphics/GUI_element.hpp"
#include "graphics/GUI_manager.hpp"

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

    auto player1 = std::make_shared<entities::Character>("Pete"); 
    gameboard->add_character(std::move(player1)); 

    gameboard->getCharater("Pete")->addStat({"HP", 100, 10});

    std::shared_ptr<graphics::GUI_manager> gui_manager = std::make_shared<graphics::GUI_manager>();

    std::shared_ptr<graphics::GUI_element> dicemenu = std::make_shared<graphics::DiceMenu>( 
        settings, 
        gameboard, 
        sf::Vector2f{150.f, 50.f}, 
        sf::Vector2f{10.f, 10.f}
    );

    gui_manager->addElement(dicemenu);
    auto selectionmenu = std::make_shared<graphics::SelectionMenu>(
        settings,
        std::vector{std::string{"eins"}, std::string{"zewi"}, std::string{"hallo drei"}},
        sf::Vector2f{100.f, 50.f},
        sf::Vector2f{60.f, 30.f},
        sf::Vector2f{0.f, 0.f}
    );
    gui_manager->addElement(selectionmenu);
    gui_manager->focusAll();


    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }
            gui_manager->handleEvent(event);
        }
        window.clear(sf::Color::Black);
        gui_manager->draw(window);
        window.display(); 
    }

    return 0;
}