#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "Player.hpp"

#include "Bullet.hpp"
#include <vector>
#include <algorithm>

#include "Enemy.hpp"
#include <cstdlib> // rand
#include <ctime> // srand

static const unsigned int screenWidth = 1200u;
static const unsigned int screenHeight = 1000u;



int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({screenWidth, 1000u}), "Space Defender");
    window.setFramerateLimit(144);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed RNG

    Player player;

    std::vector<Bullet> bullets;
    sf::Clock clock;
    sf::Clock fireCooldownClock; 
    
    std::vector<Enemy> enemies;
    sf::Clock enemySpawnClock;
    float enemySpawnInterval = 3.0f;

    std::cout << "Starting Space Defender v-1.2" << std::endl;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    
        // Handle shooting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (fireCooldownClock.getElapsedTime().asSeconds() > 0.2f) {
                sf::Vector2f spawnPos = player.getPosition();
                bullets.emplace_back(spawnPos);
                fireCooldownClock.restart();
            }
        }

        // Handle enemy spawn
        if (enemySpawnClock.getElapsedTime().asSeconds() > enemySpawnInterval) {
            float x = static_cast<float>(std::rand() % static_cast<int>(screenWidth - 40)) + 20.f;
            enemies.emplace_back(sf::Vector2f(x, -40.f));
            enemySpawnClock.restart();
        }

        // Updates
        player.update(deltaTime);
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].update(deltaTime);
        }
        for (size_t i = 0; i < enemies.size(); i++) {
            enemies[i].update(deltaTime);
        }
        auto newEnd = std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) {
            return b.isOffScreen();
        });

        bullets.erase(newEnd, bullets.end());

        window.clear();

        // Draw
        player.draw(window);
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].draw(window);
        }
        for (size_t i = 0; i < enemies.size(); i++) {
            enemies[i].draw(window);
        }
        window.display();
    }

    return 0;
}