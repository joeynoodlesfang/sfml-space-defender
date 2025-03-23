#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape shape;
    float speed = 300.0f;
};