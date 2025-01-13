#pragma once
#include "Entity.h"

class Entity;

class Enemies :
	public Entity
{
private:
	//Variables

	//Initializers
	void initComponents(sf::Texture& texture_sheet);

public:
	Enemies(float x, float y, sf::Texture& texture_sheet);
	virtual ~Enemies();

	void updateAnimation(const float& dt);
	virtual void update(const float& dt, sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);
};

