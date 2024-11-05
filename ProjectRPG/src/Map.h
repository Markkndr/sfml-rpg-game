#pragma onc
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tile.h"

class Map
{
public:

	Map();
	~Map();

	void Initialize();
	void Load();
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Texture tileSheetTexture;

	Tile* tiles;

private:

	static const int mapSize = 6;
	int mapWidth;
	int mapHeight;

	int mapNumbers[mapSize] = {
		13, 13, 13,
		14, 14, 14
	};

	sf::Sprite mapSprites[mapSize];
	int totalTiles;
	int tileWidth;
	int tileHeight;
	int totalTilesX;
	int totalTilesY;
	float scale;

};

