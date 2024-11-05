#pragma once
#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "Projectile.h"

class Player
{
public:

	Player();
	~Player();

	void Initialize();
	void Load();
	void Update(float deltaTime, Enemy& enemy, sf::Vector2f& mousePosition);
	void Draw(sf::RenderWindow& window);
	
	sf::Sprite sprite;
	sf::Vector2f size;
	sf::Vector2f scale;

private:

	sf::Texture texture;
	sf::RectangleShape boundingRectangle;
	std::vector <Projectile> projectiles;

	float playerSpeed;
	float fireRate;
	double fireRateTimer;
	int damage;
};