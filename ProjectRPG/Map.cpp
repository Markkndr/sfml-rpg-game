#include "Map.h"

Map::Map() :
    tileHeight(160), tileWidth(160), totalTilesX(0), totalTilesY(0), scale(2)
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
    if (!texture.loadFromFile("Assets/World/Tiles/TileSetTest.png"))
    {
        std::cout << "FAILED TO LOAD TILESET" << std::endl;
    }
    else
    {
        totalTilesX = texture.getSize().x / tileWidth;
        totalTilesY = texture.getSize().y / tileHeight;

        std::cout << "TileSet loaded! " << std::endl;

        for (size_t i = 0; i < spritesSize; i++)
        {
            sprites[i].setTexture(texture);
            sprites[i].setTextureRect(sf::IntRect(i * tileWidth, 0 * tileHeight, tileWidth, tileHeight));
            sprites[i].setScale(scale, scale);
            sprites[i].setPosition(0 + i * tileWidth * scale, 0);
        }
    }
}

void Map::Update(float deltaTime)
{

}

void Map::Draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < spritesSize; i++)
    {
        window.draw(sprites[i]);
    }
}
