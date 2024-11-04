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

	int mapNumbers[6] = {
		13, 13, 13,
		14, 14, 14
	};

	sf::Sprite mapSprites[6];
	int totalTiles;
	int tileWidth;
	int tileHeight;
	int totalTilesX;
	int totalTilesY;
	float scale;

};

