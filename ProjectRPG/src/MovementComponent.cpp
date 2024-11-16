#include "MovementComponent.h"

//Initializers
void MovementComponent::initVariables()
{
}

//Const and Destr
MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity,const float acceleration,const float deceleration) :
	sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

//Accessors
const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0)
		{
			return true;
		}
		break;
	case MOVING:
		if (this->velocity.x != 0.f && this->velocity.y != 0)
		{
			return true;
		}
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
		{
			return true;
		}
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
		{
			return true;
		}
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
		{
			return true;
		}
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
		{
			return true;
		}
		break;
	}
	return false;
}

//Functions

void MovementComponent::move(const float dir_x, const float dir_y, const float dt)
{
	//Acceleration
	this->velocity.x += this->acceleration * dir_x;

	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	//Deceleration x
	if (this->velocity.x > 0.f) //Check for right
	{

		//Max velocity check positive
		if (this->velocity.x > this->maxVelocity)
		{
			this->velocity.x = maxVelocity;
		}

		//Deceleration positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	else if(this->velocity.x < 0.f) //Check for left
	{
		//Max velocity check negative
		if (this->velocity.x < -this->maxVelocity)
		{
			this->velocity.x = -maxVelocity;
		}

		//Deceleration negative
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	//Deceleration y
	if (this->velocity.y > 0.f) //Check for right
	{

		//Max velocity check positive
		if (this->velocity.y > this->maxVelocity)
		{
			this->velocity.y = maxVelocity;
		}

		//Deceleration positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
		{				   
			this->velocity.y = 0.f;
		}
	}
	else if (this->velocity.y < 0.f) //Check for left
	{
		//Max velocity check negative
		if (this->velocity.y < -this->maxVelocity)
		{
			this->velocity.y = -maxVelocity;
		}

		//Deceleration negative
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
		{
			this->velocity.y = 0.f;
		}
	}


	//Final move
	this->sprite.move(this->velocity * dt); //Uses velocity
}
