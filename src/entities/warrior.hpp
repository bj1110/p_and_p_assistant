#pragma once
#include "character.hpp"

namespace entities{

class Warrior : public Character{
public: 
    int hp = 70;
    int damage = 80;
    int accuracy = 50;
    int speed = 50;
    Warrior(const std::string& name);

    int attack() const override; 
};


} //namespace entities