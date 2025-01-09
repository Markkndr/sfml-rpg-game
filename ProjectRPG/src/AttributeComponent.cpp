#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	this->level = level;
	this->expCurrent = 0;
	this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->statPoints = 3;

	this->strenght = 1;
	this->intelligence = 1;
	this->agility = 1;

	this->updateLevel();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
}

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< this->hp << "/" << this->maxHp << "\n"
		<< this->strenght << ", " << this->intelligence << ", " << this->agility << "\n"
		<< this->expCurrent << "\n"
		<< this->expNext << "\n"
		<< this->statPoints;

	return ss.str();
}

void AttributeComponent::gainExp(const unsigned exp)
{
	this->expCurrent += exp;
}

//Functions
void AttributeComponent::updateStats(const bool reset)
{
	this->maxHp = this->strenght * 10;
	this->attackDmgMin = this->strenght * 2 + this->strenght;
	this->attackDmgMax = this->strenght * 3 + this->strenght;

	this->movementSpeed = this->agility * 1.2;
	this->attackSpeed = this->agility * 1.5;

	this->abilityPowerMin = this->intelligence * 10;
	this->abilityPowerMax = this->intelligence * 20;

	if (reset)
	{
		this->hp = maxHp;
	}
}

void AttributeComponent::updateLevel()
{
	while (this->expCurrent >= this->expNext)
	{
		this->expCurrent -= this->expNext;
		++this->level;
		this->expNext = static_cast<unsigned>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
		++this->statPoints;
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}
