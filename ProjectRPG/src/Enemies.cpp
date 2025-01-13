#include "stdafx.h"
#include "Enemies.h"

//Initializers
void Enemies::initComponents(sf::Texture& texture_sheet)
{
	this->createHitboxComponent(this->sprite, 0, 0, 0, 0);
	this->createMovementComponent(0, 0, 0);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("ENEMY_IDLE", 11.5f, 0, 0, 0, 5, 32, 32);
}

Enemies::Enemies(float x, float y, sf::Texture& texture_sheet)
{
	this->initComponents(texture_sheet);

	this->setPosition(x, y);
}

Enemies::~Enemies()
{
}

void Enemies::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->sprite.setScale(4, 4);
		this->animationComponent->play("ENEMY_IDLE", dt);
	}
}

void Enemies::update(const float& dt, sf::Vector2f& mousePosView)
{
	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Enemies::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}
}
