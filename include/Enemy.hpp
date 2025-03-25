#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& position);
    void update(float deltaTime) const;
    void draw(sf::RenderWindow& window) const;
private:
    sf::RectangleShape shape;
};