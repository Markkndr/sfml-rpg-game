#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:

	Enemy();
	~Enemy();

	void ReduceHp(int damage);
	void Initialize();
	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Sprite sprite;
	sf::Vector2f size;
	sf::Vector2f scale;

	int health;

private:

	sf::Text displayEnemyHp;
	sf::Font font;
	sf::Texture texture;
	sf::RectangleShape boundingRectangle;
};