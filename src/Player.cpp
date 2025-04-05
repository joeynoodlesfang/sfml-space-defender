#include "Player.hpp"
#include "GameConfig.hpp"
#include <algorithm>

// TODO: set player edge boundaries
// TODO: mind player-enemy collision.
Player::Player() {
    speed = 300.f;

    shape.setRadius(50);
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(5);
    shape.setOrigin({shape.getRadius(), shape.getRadius()}); 
    shape.setPosition({600.f, 500.f}); 
}

void Player::update(float deltaTime) {
    sf::Vector2f movement;
    int screenWidth = GameConfig::get().screenWidth;
    int screenHeight = GameConfig::get().screenHeight;

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

    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = {shape.getRadius(), shape.getRadius()};

    pos.x = std::clamp(pos.x, size.x, screenWidth - size.x);
    pos.y = std::clamp(pos.y, size.y, screenHeight - size.y);

    shape.setPosition(pos);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition(void) const {
    return shape.getPosition();
}

void Player::markForDeletion(void) {
    m_markedForDeletion = true;
}

bool Player::isMarkedForDeletion(void) const {
    return m_markedForDeletion;
}