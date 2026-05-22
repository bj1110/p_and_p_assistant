#pragma once

#include <string>

namespace entities{

class Character{
public:
    std::string name;
    int hp;
    int damage;
    int accuracy;
    int speed;
    Character(const std::string& name, int hp, int dmg, int accuracy, int speed);
    virtual ~Character() = default; 

    virtual int attack() const = 0;
};


} //namespace entities