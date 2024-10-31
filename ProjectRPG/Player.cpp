#include "Player.h"
#include "Math.h"

#include <iostream>

Player::Player() :
    playerSpeed(1.2f), fireRate(250.0f), fireRateTimer(1.0f), damage(10)
{
}

Player::~Player()
{
}

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

void Player::Update(float deltaTime, Enemy& enemy, sf::Vector2f& mousePosition)
{
    sf::Vector2f playerPosition = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.setPosition(playerPosition + sf::Vector2f(1, 0) * playerSpeed * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sprite.setPosition(playerPosition + sf::Vector2f(-1, 0) * playerSpeed * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sprite.setPosition(playerPosition + sf::Vector2f(0, -1) * playerSpeed * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        sprite.setPosition(playerPosition + sf::Vector2f(0, 1) * playerSpeed * deltaTime);
    }

    fireRateTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireRateTimer >= fireRate)
    {
        projectiles.push_back(Projectile());
        int i = projectiles.size() - 1;
        projectiles[i].Initialize(playerPosition, mousePosition, 1.0f);

        fireRateTimer = 0;
    }

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].Update(deltaTime);

        if (enemy.health > 0)
        {
            if (Math::DidRectCollide(projectiles[i].GetGlobalBounds(), enemy.sprite.getGlobalBounds()))
            {
                enemy.ReduceHp(damage);
                projectiles.erase(projectiles.begin() + i);
            }
        }
    }

    boundingRectangle.setPosition(playerPosition);

    if (enemy.health > 0)
    {
        if (Math::DidRectCollide(sprite.getGlobalBounds(), enemy.sprite.getGlobalBounds()))
        {
            std::cout << "Player Collision" << std::endl;
        }
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    window.draw(boundingRectangle);

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].Draw(window);
    }
}