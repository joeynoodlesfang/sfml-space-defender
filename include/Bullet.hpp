#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(const sf::Vector2f& position);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape;
    float speed = 600.0f;
};
