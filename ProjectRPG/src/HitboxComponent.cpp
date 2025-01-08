#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float widht, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(widht, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1);
	this->hitbox.setOutlineColor(sf::Color::Cyan);

}

HitboxComponent::~HitboxComponent()
{

}

//Accessors
const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

//Modifiers
void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void HitboxComponent::setPosition(const float x, const float y) 
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - offsetX, y - offsetY);
}

//Functions
void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}

bool HitboxComponent::intersects(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}
