#pragma once

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
	//Variables
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initializers
	void initVariables();

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity,const float acceleration,const float deceleration);
	~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;
	const bool getState(const short unsigned state) const;

	//Modifier
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	//Functions

	void move(const float dir_x, const float dir_y, const float dt);
	void update(const float& dt);
};

