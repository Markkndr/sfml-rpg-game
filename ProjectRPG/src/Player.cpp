#include "stdafx.h"
#include "Player.h"

//Initializers
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents(sf::Texture& texture_sheet)
{
	this->createHitboxComponent(this->sprite, 25, 38, 45, 88);
	this->createMovementComponent(280.f, 1500.f, 700.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(0);

	this->animationComponent->addAnimation("PLAYER_IDLE", 11.5f, 0, 0, 0, 5, 64, 64);
	this->animationComponent->addAnimation("PLAYER_RUN", 9.f, 1, 0, 1, 5, 64, 64);
	this->animationComponent->addAnimation("PLAYER_ATTACK", 12.f, 2, 0, 2, 7, 64, 64);

	this->spellHitbox.setRadius(50.f);
	this->spellHitbox.setFillColor(sf::Color::Transparent);
	this->spellHitbox.setOutlineThickness(1.f);
	this->spellHitbox.setOutlineColor(sf::Color::Green);
}

//Const and Destr
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->initComponents(texture_sheet);
}

Player::~Player()
{
}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

bool Player::getAttacking()
{
	return this->attacking;
}

//Functions
void Player::loseHp(const int hp)
{
	this->attributeComponent->loseHp(hp);
}

void Player::gainHp(const int hp)
{
	this->attributeComponent->gainHp(hp);
}

void Player::gainExp(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack(const float& dt, sf::Vector2f& mousePosView)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dt)
	{
		this->attacking = true;

		this->spellHitbox.setPosition(
			mousePosView.x - spellHitbox.getRadius(),
			mousePosView.y - spellHitbox.getRadius()
		);
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//set origin depending on direction
		if (this->sprite.getScale().x > 0.f) // left
		{
			this->sprite.setOrigin(8, 0);

		}
		else //right
		{
			this->sprite.setOrigin(48+8, 0);
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

void Player::update(const float& dt, sf::Vector2f& mousePosView)
{
	this->movementComponent->update(dt);
	this->attributeComponent->update();
	//system("cls");
	//std::cout << this->attributeComponent->debugPrint() << std::endl;

	this->updateAttack(dt, mousePosView);
	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());
		target.draw(this->sprite, shader);
		if (this->attacking)
		{
			shader->setUniform("hasTexture", true);
			shader->setUniform("lightPos", this->getCenter());
			target.draw(this->spellHitbox, shader);
		}
	}
	else
	{
		target.draw(this->spellHitbox);
		target.draw(this->sprite);
	}


	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
}
