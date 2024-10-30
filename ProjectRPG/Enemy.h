#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:

	Enemy();
	~Enemy();

	void Initialize();
	void Load();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Sprite sprite;

	sf::Vector2f size;

	sf::Vector2f scale;

private:

	sf::Texture texture;

	sf::RectangleShape boundingRectangle;
};

