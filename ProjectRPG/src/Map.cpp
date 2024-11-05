#include "Map.h"

Map::Map() :
    tileHeight(160), tileWidth(160), totalTilesX(0), totalTilesY(0), scale(2), totalTiles(0), mapWidth(3), mapHeight(2), tiles(nullptr)
{

}

Map::~Map()
{

}

void Map::Initialize()
{

}

void Map::Load()
{
    if (!tileSheetTexture.loadFromFile("assets/world/tiles/tileset.png"))
    {
        std::cout << "FAILED TO LOAD TILESET" << std::endl;
    }
    else
    {

        totalTilesX = tileSheetTexture.getSize().x / tileWidth;
        totalTilesY = tileSheetTexture.getSize().y / tileHeight;

        std::cout << "TileSet loaded! " << std::endl;

        totalTiles = totalTilesX * totalTilesY;

        tiles = new Tile[totalTiles];

        for (size_t y = 0; y < totalTilesY; y++)
        {
            for (size_t x = 0; x < totalTilesX; x++)
            {
                int i = x + y * totalTilesX;
                tiles[i].id = i;
                tiles[i].position = sf::Vector2i(x * tileWidth, y * tileHeight);
            }
        }
    }

    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            int i = x + y * mapWidth;

            int index = mapNumbers[i];

            mapSprites[i].setTexture(tileSheetTexture);
            mapSprites[i].setTextureRect(sf::IntRect(
                tiles[index].position.x,
                tiles[index].position.y,
                tileWidth,
                tileHeight));

            mapSprites[i].setScale(sf::Vector2f(scale, scale));
            mapSprites[i].setPosition(sf::Vector2f(x * tileWidth * scale, y * tileHeight * scale));
        }
    }
}

void Map::Update(double deltaTime)
{

}

void Map::Draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < mapSize; i++)
    {
        window.draw(mapSprites[i]);
    }
}
