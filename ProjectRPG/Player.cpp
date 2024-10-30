#include "Player.h"
#include "Math.h"

#include <iostream>

void Player::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Cyan);
    boundingRectangle.setOutlineThickness(1);
}

void Player::Load()
{
    if (!texture.loadFromFile("Assets/Player/Textures/characters.png"))
    {
        std::cout << "FAILED TO LOAD PLAYER TEXTURE" << std::endl;
    }
    else
    {
        size = sf::Vector2f(32, 32);
        scale = sf::Vector2f(4, 4);

        std::cout << "Player Texture Loaded!" << std::endl;
        sprite.setTexture(texture);

        sprite.setTextureRect(sf::IntRect(0, 32, size.x, size.y));

        sprite.scale(sf::Vector2f(scale.x, scale.y));

        sprite.setPosition(sf::Vector2f(960, 540));

        boundingRectangle.setSize(sf::Vector2f(size.x * scale.x, size.y * scale.y));
    }
}

void Player::Update(float deltaTime, Enemy& enemy)
{
    sf::Vector2f position = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.setPosition(position + sf::Vector2f(1, 0) * playerSpeed * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sprite.setPosition(position + sf::Vector2f(-1, 0) * playerSpeed * deltaTime);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sprite.setPosition(position + sf::Vector2f(0, -1) * playerSpeed * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        sprite.setPosition(position + sf::Vector2f(0, 1) * playerSpeed * deltaTime);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::RectangleShape newBullet(sf::RectangleShape(sf::Vector2f(20, 10)));
        bullets.push_back(newBullet);

        int i = bullets.size() - 1;
        bullets[i].setPosition(sprite.getPosition());
    }

    for (size_t i = 0; i < bullets.size(); i++)
    {
        sf::Vector2f bulletDirection = enemy.sprite.getPosition() - bullets[i].getPosition();
        bulletDirection = Math::NormalizeVector(bulletDirection);
        bullets[i].setPosition(bullets[i].getPosition() + bulletDirection * bulletSpeed * deltaTime);
    }

    boundingRectangle.setPosition(position);

    if (Math::DidRectCollide(sprite.getGlobalBounds(), enemy.sprite.getGlobalBounds()))
    {
        std::cout << "Collision" << std::endl;
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    window.draw(boundingRectangle);

    for (size_t i = 0; i < bullets.size(); i++)
    {
        window.draw(bullets[i]);
    }
}
