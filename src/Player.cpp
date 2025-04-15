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

    // Health bar background (gray)
    sf::RectangleShape healthBarBack;
    healthBarBack.setSize({60.f, 8.f});
    healthBarBack.setFillColor(sf::Color(100, 100, 100)); // dark gray
    healthBarBack.setOrigin({healthBarBack.getSize().x / 2, healthBarBack.getSize().y / 2});
    healthBarBack.setPosition({shape.getPosition().x, shape.getPosition().y - shape.getRadius() - 15.f});
    window.draw(healthBarBack);

    // Health bar foreground (green -> red based on hp)
    sf::RectangleShape healthBarFront;
    float healthPercent = static_cast<float>(health) / maxHealth;
    healthBarFront.setSize({60.f * healthPercent, 8.f});
    healthBarFront.setFillColor(sf::Color::Green);
    healthBarFront.setOrigin({healthBarBack.getSize().x / 2, healthBarBack.getSize().y / 2});
    healthBarFront.setPosition(healthBarBack.getPosition());
    window.draw(healthBarFront);
}

void Player::markForDeletion(void) {
    m_markedForDeletion = true;
}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
    }
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition(void) const {
    return shape.getPosition();
}

bool Player::isMarkedForDeletion(void) const {
    return m_markedForDeletion;
}

int Player::getHealth() const {
    return health;
}

bool Player::isDead() const {
    return health <= 0;
}