#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Map
{
public:

	Map();
	~Map();

	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Sprite sprites[6];
	int spritesSize = 6;

private:

	int tileWidth;
	int tileHeight;
	int totalTilesX;
	int totalTilesY;
	int scale;

	sf::Texture texture;
};

