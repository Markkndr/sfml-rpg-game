#pragma once

class HitboxComponent
{
private:
	//Variables
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y, 
		float widht, float height);
	virtual ~HitboxComponent();

	//Functions
	void update();
	void render(sf::RenderTarget& target);

	bool checkIntersect(const sf::FloatRect& frect);
	
};

