#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& position);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen(unsigned int screenHeight) const;
private:
    sf::RectangleShape shape;
    float speed = 100.0f;
};