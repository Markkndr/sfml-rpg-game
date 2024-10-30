#pragma once
#include <SFML/Graphics.hpp>

#include "Enemy.h"

class Player
{
public:

	void Initialize();
	void Load();

	void Update(float deltaTime, Enemy& enemy);
	void Draw(sf::RenderWindow& window);
	
	sf::Sprite sprite;

	sf::Vector2f size;

	sf::Vector2f scale;

private:

	sf::Texture texture;

	std::vector<sf::RectangleShape> bullets;

	sf::RectangleShape boundingRectangle;

	float bulletSpeed = 1.0f;

	float playerSpeed = 1.2f;
};

