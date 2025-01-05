#pragma once

#include "Tile.h"

class TileMap
{
private:
	//Variables
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector< Tile* > > > map;
	sf::Texture tileTextureSheet;

public:
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	//Functions
	void update();

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void render(sf::RenderTarget& target);

};
