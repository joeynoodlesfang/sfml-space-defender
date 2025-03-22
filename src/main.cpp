#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1200u, 1000u}), "Space Defender");
    window.setFramerateLimit(144);

    sf::CircleShape shape;
    shape.setRadius(150);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(5);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({375, 275}); 
    
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

        sf::Vector2f movement;
        const float speed = 300.0f * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            movement.x -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            movement.x += speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            movement.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            movement.y += speed;
        }

        shape.move(movement);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}