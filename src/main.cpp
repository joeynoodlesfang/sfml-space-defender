#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Space Defender");
    window.setFramerateLimit(144);

    sf::CircleShape shape;
    shape.setRadius(150);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(5);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({375, 275}); 
    
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            shape.move({-1.f, 0.f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            shape.move({1.f, 0.f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            shape.move({0.f, -1.f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            shape.move({0.f, 1.f});
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}