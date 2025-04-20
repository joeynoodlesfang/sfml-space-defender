#include "GameManager.hpp"

void GameManager::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if (fireCooldownClock.getElapsedTime().asSeconds() > 0.2f) {
            spawnBullet();
            fireCooldownClock.restart();
        }
    }
}

void GameManager::update(float deltaTime) 
{
    player.update(deltaTime);
    updateBullets(deltaTime);
}

void GameManager::onEnemyEscaped()
{
    player.takeDamage(10);
}

void GameManager::spawnBullet()
{
    bullets.push_back(std::make_unique<Bullet>(player.getPosition()));
}

void GameManager::updateBullets(float deltaTime)
{

}