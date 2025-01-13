#pragma once
#include <random>
#include <vector>
#include <iostream>

#include "Tile.h"

namespace rnd
{
	std::random_device rd;
	std::mt19937 mt(rd());

	int randomInt(int exclusiveMax);
	int randomInt(int min, int max);
	bool randomBool(double probability = 0.5);
}

class MapGeneration
{
public:
	enum Tile
	{
		Unused = ' ',
		Floor = '.',
		Corridor = ',',
	};

	enum Directions
	{
		North,
		South,
		West,
		East,
		DirectionCount
	};

	//Functions
	void generate(int maxFeatures);

private:
	//Variables
	int _width, _height;
	std::vector<char> _tiles;
	std::vector<sf::RectangleShape> _rooms; // rooms for place stairs or monsters
	std::vector<sf::RectangleShape> _exits; // 4 sides of rooms or corridors

	//Functions
	char getTile();

};

