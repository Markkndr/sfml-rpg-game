#include "stdafx.h"
#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;
	this->hpBar.setSize(sf::Vector2f(200, 10));
}

PlayerGUI::~PlayerGUI()
{
}

//Functions
void PlayerGUI::update(const float& dt)
{
}

void PlayerGUI::render(sf::RenderTarget& target)
{
}
