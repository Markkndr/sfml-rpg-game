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

	this->createMovementComponent(280.f, 18.f, 7.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("PLAYER_IDLE", 12.f, 0, 0, 0, 5, 64, 64);
	this->animationComponent->addAnimation("PLAYER_RUN_RIGHT", 9.f, 1, 1, 1, 5, 64, 64);
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
		this->animationComponent->play("PLAYER_RUN_RIGHT", dt);
	}
}
