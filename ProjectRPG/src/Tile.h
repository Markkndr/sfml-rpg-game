#pragma once

enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile
{
private:
	//Variables

	//Initializers

protected:
	short type;
	bool collision;

	sf::RectangleShape shape;

public:

	Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision, short type);
	virtual ~Tile();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const bool& getCollision() const;
	const std::string getAsString() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

