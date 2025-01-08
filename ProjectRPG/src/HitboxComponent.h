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

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//Functions
	void update();
	void render(sf::RenderTarget& target);

	bool intersects(const sf::FloatRect& frect);
	
};

