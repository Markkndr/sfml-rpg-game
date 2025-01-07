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
	sf::Texture tileSheet;
	std::string textureFile;

	//Functions
	void clear();

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;

	//Functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update();

	void render(sf::RenderTarget& target);
};
