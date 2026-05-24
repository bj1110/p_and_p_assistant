#pragma once

#include <SFML/Graphics.hpp>

namespace graphics{

class ButtonShape: public sf::Shape{
public:
    explicit ButtonShape(sf::Vector2f rectangle_size = sf::Vector2f{0.f, 0.f});

    size_t getPointCount() const override;

    sf::Vector2f getPoint(size_t index) const override;

    void setRectangleSize(sf::Vector2f size);

    void setCornerSharpeness(float sharpeness);

private:

sf::Vector2f rectangle_size_ {};
float corner_sharpeness_ {10.f};


};


} //namespace graphics