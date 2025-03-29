#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "ScreenBounded.hpp"

class Enemy : public GameObject, public ScreenBounded {
public:
    Enemy(const sf::Vector2f& position);
    
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition(void) const override;

    bool isOffScreen(unsigned int screenHeight) const override;

private:
    sf::RectangleShape shape;
    float speed = 100.0f;
};