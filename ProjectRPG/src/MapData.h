#pragma once
#include <string>

struct MapData
{
	int version;

	std::string tilesheet;
	std::string name;
	
	int tile_width = 0;
	int tile_height = 0;

	int scale_x = 0;
	int scale_y = 0;

	int dataLength = 0;
	int* data = nullptr;
};