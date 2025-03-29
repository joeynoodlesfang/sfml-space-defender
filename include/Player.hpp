#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Player : public GameObject{
public:
    Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;

    sf::Vector2f getPosition(void);

private:
    sf::CircleShape shape;
    float speed = 300.0f;
};