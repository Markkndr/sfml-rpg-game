#include "MapLoader.h"
#include <fstream>

#include "MapData.h"

void MapLoader::Load(std::string filename)
{
	MapData mapData;

	std::string line;
	std::ifstream file(filename);

	bool isMapValid = false;

	if (!file.is_open())
	{
		std::cout << "Unable to open " << filename << std::endl;
	}
	else
	{
		while (std::getline(file, line))
		{
			if (!isMapValid)
			{
				if (line == "[Map]")
				{
					isMapValid = true;
					continue;
				}
				else
				{
					std::cout << "rmap file is not valid" << std::endl;
					break;
				}
			}

			if (isMapValid)
			{
				try
				{
					int count = line.find('=');
					std::string variable = line.substr(0, count);
					std::string value = line.substr(count + 1, line.length() - count);

					if (variable == "version")
					{
						mapData.version = std::stoi(value);
					}
					if (variable == "tilesheet")
					{
						mapData.tilesheet = value;
					}
					else if (variable == "name")
					{
						mapData.name = value;
					}
					else if (variable == "tile_width")
					{
						mapData.tile_width = std::stoi(value);
					}
					else if (variable == "tile_height")
					{
						mapData.tile_height = std::stoi(value);
					}
					else if (variable == "scale_x")
					{
						mapData.scale_x = std::stoi(value);
					}
					else if (variable == "scale_y")
					{
						mapData.scale_y = std::stoi(value);
					}
					else if (variable == "dataLength")
					{
						mapData.dataLength = std::stoi(value);
					}
					else if (variable == "data")
					{
						mapData.data = new int[mapData.dataLength];

						int offset = 0;
						int i = 0;

						while(true)
						{
							int count = value.find(',', offset);
							std::string mapIndex = value.substr(offset, count - offset);

							if (mapIndex == ";")
								break;

							mapData.data[i] = std::stoi(mapIndex);

							offset = count + 1;
							i++;
						}
					}
				}
				catch (const std::exception&)
				{
					std::cout << "Error reading file --> " << filename << std::endl;
				}
			}
		}
		file.close();
	}
}