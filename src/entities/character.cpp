#include "character.hpp"

namespace entities{

Character::Character (const std::string& name, int hp, int dmg, int accuracy, int speed):
    name(name), hp(hp), damage(dmg), accuracy(accuracy), speed(speed) {}


} //namespace entities