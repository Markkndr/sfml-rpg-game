#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Projectile
{
public:

	Projectile();
	~Projectile();

	void Initialize(const sf::Vector2f& position,const sf::Vector2f& target, float speed);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	inline const sf::FloatRect GetGlobalBounds() { return rectangleShape.getGlobalBounds(); }

private:

	sf::Vector2f direction;
	sf::RectangleShape rectangleShape;
	std::vector<sf::RectangleShape> projectiles;

	float m_speed;

};