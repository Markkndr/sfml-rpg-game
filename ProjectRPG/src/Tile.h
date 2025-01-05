#pragma once

class Tile
{
private:
	//Variables

	//Initializers

protected:
	sf::RectangleShape shape;

public:
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect);
	virtual ~Tile();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

