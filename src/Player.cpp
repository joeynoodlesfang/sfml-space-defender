#include "Player.hpp"

Player::Player() {
    shape.setRadius(50);
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(5);
    shape.setOrigin({shape.getRadius(), shape.getRadius()}); 
    shape.setPosition({600.f, 500.f}); 
}

void Player::update(float deltaTime) {
    sf::Vector2f movement;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        movement.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        movement.y += speed * deltaTime;

    shape.move(movement);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Player::getPosition(void) {
    return shape.getPosition();
}