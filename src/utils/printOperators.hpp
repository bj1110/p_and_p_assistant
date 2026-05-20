#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

inline std::ostream& operator<<(std::ostream& os, const sf::Vector2f vec){
    os << "("<<vec.x<<", "<< vec.y<< ")";
    return os; 
}

inline std::string to_string(const sf::Vector2f& vec){
    return "("+ std::to_string( vec.x) +", "+ std::to_string(vec.y)+ ")";
}