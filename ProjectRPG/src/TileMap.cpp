#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				for (int k = 0; k < this->map[x][y][z].size(); k++)
				{
					delete this->map[x][y][z][k];
					this->map[x][y][z][k] = NULL;
				}
				this->map[x][y][z].clear();
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();

	//std::cout << this->map.size() << std::endl;
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector< Tile* > > >());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector< Tile* > >());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
	{
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILESHEET::FILENAME: " << texture_file << std::endl;
	}

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineThickness(-1.f);
	this->collisionBox.setOutlineColor(sf::Color::Red);
}

TileMap::~TileMap()
{
	this->clear();
}

//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int z) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (z >= 0 && z < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][z].size();
			}
		}
	}

	return -1;
}

//Functions
void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	//Take three indicies from mouse pos in the grid and add tile to that pos if the internal tilemap array allows it
	if (x < this->maxSizeWorldGrid.x && x >= 0 && y < this->maxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0)
	{		
		//Ok to add tile
		this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type));
		
		//std::cout << "DEBUG: ADDED TILE!" << std::endl;
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	//Take three indicies from mouse pos in the grid and remove a tile from that pos if the internal tilemap array allows it
	if (x < this->maxSizeWorldGrid.x && x >= 0 && y < this->maxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			//Ok to remove tile
			delete this->map[x][y][z][this->map[x][y][z].size()-1];
			this->map[x][y][z].pop_back();

			std::cout << "DEBUG: REMOVED TILE!" << std::endl;
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/*SAVES TILEMAP TO TEXT-FILE
	* Format:
	* 
	* Basic:
	* Size x y 
	* gridSize
	* layers
	* texture file
	* 
	* All tiles:
	* gridPos x y z (all tiles), Texture rect x y, collision, type
	*/

	std::ofstream out_file;
	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (int k = 0; k < map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " <<
							this->map[x][y][z][k]->getAsString() << " ";
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << std::endl;
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;
	in_file.open(file_name);
	
	if (in_file.is_open())
	{
		sf::Vector2u size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;
	
		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;
	
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector< Tile* > > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector< Tile* > >());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector< Tile* >());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
		{
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILESHEET::FILENAME: " << texture_file << std::endl;
		}

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z].push_back
			(
				new Tile(
					x, y, 
					this->gridSizeF, this->tileSheet, 
					sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), 
					collision, type)
			);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << std::endl;
	}
	
	in_file.close();
}

void TileMap::updateCollision(Entity* entity, const float& dt)
{

	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > maxSizeWorldF.x)
	{
		entity->setPosition(maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
	//Tiles
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 12;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSizeWorldGrid.x)
	{
		this->fromX = this->maxSizeWorldGrid.x;
	}

	this->toX = entity->getGridPosition(this->gridSizeI).x + 13;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSizeWorldGrid.x)
	{
		this->toX = this->maxSizeWorldGrid.x;
	}
	
	this->fromY = entity->getGridPosition(this->gridSizeI).y - 8;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSizeWorldGrid.y)
	{
		this->fromY = this->maxSizeWorldGrid.y;
	}
	
	this->toY = entity->getGridPosition(this->gridSizeI).y + 10;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSizeWorldGrid.y)
	{
		this->toY = this->maxSizeWorldGrid.y;
	}

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPosBounds = entity->getNextPosBounds(dt);

				if (this->map[x][y][this->layer][k]->getCollision() &&
					this->map[x][y][this->layer][k]->intersects(playerBounds))
				{
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						//std::cout << "TOP COLLISION" << std::endl;
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						//std::cout << "BOTTOM COLLISION" << std::endl;
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						//std::cout << "RIGHT COLLISION" << std::endl;
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						//std::cout << "LEFT COLLISION" << std::endl;
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, const bool show_collision)
{
	this->layer = 0;

	this->fromX = gridPosition.x - 15;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->maxSizeWorldGrid.x)
	{
		this->fromX = this->maxSizeWorldGrid.x;
	}

	this->toX = gridPosition.x + 16;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->maxSizeWorldGrid.x)
	{
		this->toX = this->maxSizeWorldGrid.x;
	}

	this->fromY = gridPosition.y - 10;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->maxSizeWorldGrid.y)
	{
		this->fromY = this->maxSizeWorldGrid.y;
	}

	this->toY = gridPosition.y + 11;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->maxSizeWorldGrid.y)
	{
		this->toY = this->maxSizeWorldGrid.y;
	}

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::DEFERRED)
				{
					this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
				}
				else
				{
					this->map[x][y][this->layer][k]->render(target);
				}

				if (show_collision)
				{
					if (this->map[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}

void TileMap::renderDeferred(sf::RenderTarget& target)
{
	while (!this->deferredRenderStack.empty())
	{
		deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}
