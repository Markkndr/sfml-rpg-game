#include "stdafx.h"
#include "Player.h"

//Initializers
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{

}

//Const and Destr
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 25, 38, 45, 88);
	this->createMovementComponent(280.f, 1500.f, 700.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(0);

	this->animationComponent->addAnimation("PLAYER_IDLE", 11.5f, 0, 0, 0, 5, 64, 64);
	this->animationComponent->addAnimation("PLAYER_RUN", 9.f, 1, 0, 1, 5, 64, 64);
	this->animationComponent->addAnimation("PLAYER_ATTACK", 12.f, 1, 0, 1, 7, 128, 64);
}

Player::~Player()
{
}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

//Functions
void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//set origin depending on direction
		if (this->sprite.getScale().x > 0.f) // left
		{
			this->sprite.setOrigin(64, 0);

		}
		else //right
		{
			this->sprite.setOrigin(48+64, 0);
		}
		//animate and check for anim end
		if (this->animationComponent->play("PLAYER_ATTACK", dt, true))
		{

			this->attacking = false;

			//set origin depending on direction
			if (this->sprite.getScale().x > 0.f) // left
			{
				this->sprite.setOrigin(0, 0); 

			}
			else //right
			{
				this->sprite.setOrigin(48, 0);
			}
		}
	}
	else if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("PLAYER_IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0, 0);
			this->sprite.setScale(scale, scale);
		}
		this->animationComponent->play("PLAYER_RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(48, 0);
			this->sprite.setScale(-scale, scale);
		}
		this->animationComponent->play("PLAYER_RUN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("PLAYER_RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("PLAYER_RUN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
	{
		this->attributeComponent->gainExp(2);
	}
	this->movementComponent->update(dt);

	this->attributeComponent->update();
	system("cls");
	std::cout << this->attributeComponent->debugPrint() << std::endl;

	this->updateAttack();
	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
