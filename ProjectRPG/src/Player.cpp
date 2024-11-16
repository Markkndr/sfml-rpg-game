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

	this->createMovementComponent(300.f, 20.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 12.f, 0, 0, 0, 5, 64, 64);
}

Player::~Player()
{
}

//Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->animationComponent->play("IDLE_LEFT", dt);
}
