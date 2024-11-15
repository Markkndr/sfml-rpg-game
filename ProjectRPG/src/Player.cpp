#include "Player.h"

//Initializers
void Player::initVariables()
{
}

void Player::initComponents()
{
	this->createMovementComponent(300.f, 20.f, 5.f);
}

//Const and Destr
Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{
}
