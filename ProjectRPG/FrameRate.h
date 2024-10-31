#pragma once
#include <SFML/Graphics.hpp>

class FrameRate
{
public:

	FrameRate();
	~FrameRate();

	void Initialize();
	void Load();

	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
	
private:

	sf::Text displayFrameRate;
	sf::Font font;

	float timer;
};