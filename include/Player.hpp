#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Player : public GameObject{
public:
    Player();

    void update(float deltaTime, const unsigned int screenWidth, const unsigned int screenHeight) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition(void) const override;
    void markForDeletion(void) override;
    bool isMarkedForDeletion(void) const override;

private:
    sf::CircleShape shape;
};