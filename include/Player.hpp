#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Player : public GameObject{
public:
    Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    void markForDeletion(void) override;
    void takeDamage(int amount);

    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition(void) const override;
    bool isMarkedForDeletion(void) const override;
    int getHealth() const;
    bool isDead() const;

private:
    sf::CircleShape shape;
    int health = 3;
    int maxHealth = 3;
};