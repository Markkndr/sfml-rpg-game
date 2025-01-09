#pragma once
#include "Player.h"

class Player;

class PlayerGUI
{
private:
	Player* player;
	sf::RectangleShape hpBar;

public:
	PlayerGUI(Player* player);
	~PlayerGUI();

	//Functions
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

