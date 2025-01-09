#pragma once

#include "Tile.h"
#include "Entity.h"

class Entity;

class TileMap
{
private:
	//Variables
	float gridSizeF;
	int gridSizeI;
	int layers;

	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	std::vector< std::vector< std::vector< std::vector< Tile* > > > > map;
	sf::Texture tileSheet;
	std::string textureFile;
	sf::RectangleShape collisionBox;
	std::stack <Tile*> deferredRenderStack;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	//Functions
	void clear();

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int z) const;

	//Functions
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const int x, const int y, const int z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& dt);

	void update();

	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);
	void renderDeferred(sf::RenderTarget& target);
};
