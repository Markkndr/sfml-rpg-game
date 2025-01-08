#pragma once

#include "Tile.h"
#include "Entity.h"

class Entity;

class TileMap
{
private:
	//Variables
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	sf::Vector2u maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	std::vector< std::vector< std::vector< Tile* > > > map;
	sf::Texture tileSheet;
	std::string textureFile;
	sf::RectangleShape collisionBox;

	//Functions
	void clear();

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;

	//Functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity);

	void update();

	void render(sf::RenderTarget& target, Entity* entity = NULL);
};
