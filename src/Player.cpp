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

    // use WASD to prevent key ghosting
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += speed * deltaTime;

    shape.move(movement);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Player::getPosition(void) {
    return shape.getPosition();
}