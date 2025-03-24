#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "Player.hpp"

#include "Bullet.hpp"
#include <vector>
#include <algorithm>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1200u, 1000u}), "Space Defender");
    window.setFramerateLimit(144);

    Player player;
    std::vector<Bullet> bullets;
    sf::Clock clock;
    sf::Clock fireCooldownClock; 

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

        player.update(deltaTime);
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].update(deltaTime);
        }
        auto newEnd = std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) {
            return b.isOffScreen();
        });

        bullets.erase(newEnd, bullets.end());

        window.clear();
        player.draw(window);
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].draw(window);
        }
        window.display();
    }

    return 0;
}