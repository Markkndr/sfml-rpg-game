#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>


sf::Vector2f NormalizeVector(sf::Vector2f vector)
{
    float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    sf::Vector2f normalizedVector;

    normalizedVector.x = vector.x / m;
    normalizedVector.y = vector.y / m;
    
    return normalizedVector;
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG Game", sf::Style::Default, settings);

    std::vector<sf::RectangleShape> bullets;

    float bulletSpeed = 1.0f;
        //LOAD

    //player
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    if (!playerTexture.loadFromFile("Assets/Player/Textures/characters.png"))
    {   
        std::cout << "FAILED TO LOAD PLAYER TEXTURE" << std::endl;
    }
    else
    {   
        std::cout << "Player Texture Loaded!" << std::endl;
        playerSprite.setTexture(playerTexture);

        playerSprite.setTextureRect(sf::IntRect(0, 32, 32, 32));

        playerSprite.scale(sf::Vector2f(4, 4));

        playerSprite.setPosition(sf::Vector2f(1650, 800));
    }
    //player

    //slime
    sf::Texture slimeTexture;
    sf::Sprite slimeSprite;

    if (!slimeTexture.loadFromFile("Assets/Slime/Texture/Slime.png"))
    {   
        std::cout << "FAILED TO LOAD SLIME TEXTURE" << std::endl;
    }
    else
    {   
        std::cout << "Slime Texture Loaded!" << std::endl;
        slimeSprite.setTexture(slimeTexture);
        slimeSprite.setPosition(sf::Vector2f(400, 700));

        slimeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

        slimeSprite.scale(sf::Vector2f(4, 4));
    }
    //slime
    
        //LOAD

    //MAIN GAME LOOP
    while (window.isOpen())
    {
        //UPDATE
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();           
        }

        //sf::Vector2f bulletPosition = bullet.getPosition();
        //bullet.setPosition(bulletPosition + bulletDirection * bulletSpeed);

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0.5, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(-0.5, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, -0.5));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, 0.5));
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {   
            sf::RectangleShape newBullet(sf::RectangleShape(sf::Vector2f(50, 25)));
            bullets.push_back(newBullet);

            int i = bullets.size() - 1;
            bullets[i].setPosition(playerSprite.getPosition());
        }
        //UPDATE

        for (size_t i = 0; i < bullets.size(); i++)
        {
            sf::Vector2f bulletDirection = slimeSprite.getPosition() - bullets[i].getPosition();
            bulletDirection = NormalizeVector(bulletDirection);
            bullets[i].setPosition(bullets[i].getPosition() + bulletDirection * bulletSpeed);
        }

        //DRAW
        window.clear(sf::Color::Black);
        for (size_t i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i]);
        }
        window.draw(slimeSprite);
        window.draw(playerSprite);
        window.display();
        //DRAW
    }
    return 0;
}