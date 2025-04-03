#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "ScreenBounded.hpp"

class Bullet : public GameObject, public ScreenBounded {
public:
    Bullet(const sf::Vector2f& position);

    void update(float deltaTime, const unsigned int screenWidth, const unsigned int screenHeight) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition(void) const override;
    bool isOffScreen(unsigned int screenHeight) const override;
    void markForDeletion(void) override;
    bool isMarkedForDeletion(void) const override;

private:
    sf::RectangleShape shape;
};
