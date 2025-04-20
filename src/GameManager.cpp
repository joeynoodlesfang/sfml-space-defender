#include "GameManager.hpp"
#include "EntityUtils.hpp" //TODO should this be here or in hpp?

//TODO
//Make sure GameManager is singleton as well (does that make sense)
//Handling bullet collision

void GameManager::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        spawnBullet();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        bullets.clear();
    }
}

void GameManager::update(float deltaTime) 
{
    player.update(deltaTime);
    updateBullets(deltaTime);
}

void GameManager::onEnemyEscaped()
{
    //TODO Should not be health damage, but some count reduction
    player.takeDamage(10);
}

void GameManager::spawnBullet()
{
    if (bulletSpawnCDClock.getElapsedTime().asSeconds() > 0.2f) {
        bullets.push_back(std::make_unique<Bullet>(player.getPosition()));
        bulletSpawnCDClock.restart();
    }
}

void GameManager::updateBullets(float deltaTime)
{
    updateEntities(bullets, deltaTime);
}