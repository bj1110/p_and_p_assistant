#include "buttonShape.hpp"
#include <cmath>

namespace graphics{

ButtonShape::ButtonShape(sf::Vector2f rectangle_size)
:rectangle_size_(rectangle_size)
{
    update();
}

size_t ButtonShape::getPointCount() const{
    return 50;
}

void ButtonShape::setRectangleSize(sf::Vector2f size){
    rectangle_size_ = size;
    update(); 
}

sf::Vector2f ButtonShape::getPoint(size_t index) const{
    static constexpr float pi = 3.141592654f;

    float t = index * 2.f * pi / getPointCount();

    float n = 10.f;

    float ct = std::cos(t);
    float st = std::sin(t);

    float x = std::copysign(std::pow(std::abs(ct), 2.f / n), ct) * rectangle_size_.x;
    float y = std::copysign(std::pow(std::abs(st), 2.f / n), st) * rectangle_size_.y;

    return rectangle_size_ + sf::Vector2f(x, y);
}


} //namespace graphics