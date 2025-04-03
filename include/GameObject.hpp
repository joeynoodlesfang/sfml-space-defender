#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual void update(float deltaTime, const unsigned int screenWidth, const unsigned int screenHeight) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void markForDeletion() = 0;
    virtual bool isMarkedForDeletion() const = 0;

    virtual ~GameObject() = default;

protected:
    sf::Vector2f m_position;
    float speed = 0.0f;
    bool m_markedForDeletion = false;
};