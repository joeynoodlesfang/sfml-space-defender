#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "Player.hpp"
int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1200u, 1000u}), "Space Defender");
    window.setFramerateLimit(144);

    Player player;
    sf::Clock clock;
    
    std::cout << "Starting Space Defender v-1" << std::endl;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        player.update(deltaTime);

        window.clear();
        player.draw(window);
        window.display();
    }

    return 0;
}