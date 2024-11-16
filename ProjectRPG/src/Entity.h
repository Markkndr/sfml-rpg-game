#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	//Initialize
	void initVariables();

protected:

	sf::Texture* texture;
	sf::Sprite sprite;

	float scale;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	//Component Functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//FUNCTIONS
	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

};

