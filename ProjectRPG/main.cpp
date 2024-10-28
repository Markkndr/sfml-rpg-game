#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG Game", sf::Style::Default, settings);

        //Load

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
        slimeSprite.setPosition(sf::Vector2f(400, 100));

        slimeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

        slimeSprite.scale(sf::Vector2f(4, 4));
    }
    //slime
    
        //Load

    //main game loop
    while (window.isOpen())
    {
        //UPDATE
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();           
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0.04, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(-0.04, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, -0.04));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            sf::Vector2f position = playerSprite.getPosition();
            playerSprite.setPosition(position + sf::Vector2f(0, 0.04));
        }
        //UPDATE

        //DRAW
        window.clear(sf::Color::Black);

        window.draw(slimeSprite);

        window.draw(playerSprite);

        window.display();
        //DRAW
    }
    return 0;
}