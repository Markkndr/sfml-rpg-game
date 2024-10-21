#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG Game", sf::Style::Default, settings);

    sf::CircleShape shape(50.f, 3);
    shape.setPosition(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineThickness(5.f);
    shape.setOutlineColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        window.draw(shape);

        window.display();
    }
    
    return 0;
}