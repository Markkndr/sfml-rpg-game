#pragma once
#include <SFML/Graphics.hpp>

class FrameRate
{
public:

	void Initialize();
	void Load();

	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
	
	FrameRate();
	~FrameRate();

private:

	sf::Text displayFrameRate;
	sf::Font font;

	float timer;
};

