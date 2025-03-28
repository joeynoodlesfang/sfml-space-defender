#include "Enemy.hpp"

Enemy::Enemy(const sf::Vector2f& position) {
    shape.setSize({40.f, 40.f});
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setPosition(position);
}

void Enemy::update(float deltaTime) {
    sf::Vector2f movement(0.f, speed * deltaTime);
    shape.move(movement);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

//TODO: collision still wrong, now whole object blinks off.
bool Enemy::isOffScreen(unsigned int screenHeight) const {
    return shape.getPosition().y + shape.getSize().y / 2.f > screenHeight;
}