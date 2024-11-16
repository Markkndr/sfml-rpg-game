#include "Player.h"

//Initializers
void Player::initVariables()
{
}

void Player::initComponents()
{

}

//Const and Destr
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 25, 32, 45, 92);
	this->createMovementComponent(280.f, 18.f, 7.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("PLAYER_IDLE", 12.5f, 0, 0, 0, 5, 64, 64);
	this->animationComponent->addAnimation("PLAYER_RUN", 9.5f, 1, 1, 1, 5, 64, 64);
	this->animationComponent->addAnimation("PLAYER_ATTACK", 12.f, 2, 2, 2, 5, 64, 64);
}

Player::~Player()
{
}

//Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("PLAYER_IDLE", dt);
	}
	else if(this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0, 0);
		this->sprite.setScale(scale, scale);
		this->animationComponent->play("PLAYER_RUN", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(48, 0);
		this->sprite.setScale(-scale, scale);
		this->animationComponent->play("PLAYER_RUN", dt);
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("PLAYER_RUN", dt);
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("PLAYER_RUN", dt);
	}

	this->hitboxComponent->update();
}
