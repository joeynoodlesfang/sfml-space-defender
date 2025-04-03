#include "Enemy.hpp"

Enemy::Enemy(const sf::Vector2f& position) {
    speed = 100.f;
    
    shape.setSize({40.f, 40.f});
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setPosition(position);
}

void Enemy::update(float deltaTime, const unsigned int screenWidth, const unsigned int screenHeight) {
    sf::Vector2f movement(0.f, speed * deltaTime);
    shape.move(movement);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition(void) const {
    return shape.getPosition();
}

bool Enemy::isOffScreen(unsigned int screenHeight) const {
    return shape.getPosition().y - shape.getSize().y / 2.f > screenHeight;
}

void Enemy::markForDeletion(void) {
    m_markedForDeletion = true;
}

bool Enemy::isMarkedForDeletion(void) const {
    return m_markedForDeletion;
}