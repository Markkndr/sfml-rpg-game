#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);
}

void Enemy::Load()
{
    if (!texture.loadFromFile("Assets/Slime/Texture/Slime.png"))
    {
        std::cout << "FAILED TO LOAD SLIME TEXTURE" << std::endl;
    }
    else
    {
        size = sf::Vector2f(32, 32);
        scale = sf::Vector2f(4, 4);

        std::cout << "Slime Texture Loaded!" << std::endl;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(400, 700));

        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));

        sprite.scale(sf::Vector2f(scale.x, scale.y));

        boundingRectangle.setSize(sf::Vector2f(size.x * scale.x, size.y * scale.y));
    }
}

void Enemy::Update(float deltaTime)
{
    sf::Vector2f position = sprite.getPosition();

    boundingRectangle.setPosition(position);
}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    window.draw(boundingRectangle);
}