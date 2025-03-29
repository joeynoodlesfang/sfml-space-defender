#include "Bullet.hpp"

Bullet::Bullet(const sf::Vector2f& position) {
    shape.setSize({8.f, 20.f});
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);
    shape.setOrigin(shape.getSize() / 2.f);
}

void Bullet::update(float deltaTime) {
    sf::Vector2f movement(0.f, -speed * deltaTime);
    shape.move(movement);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Bullet::getPosition(void) const {
    return shape.getPosition();
}

bool Bullet::isOffScreen(unsigned int screenHeight) const {
    return shape.getPosition().y + shape.getSize().y < 0;
}

