#pragma once
#include "Player.h"
#include "Gui.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player;

	sf::VideoMode& vm;

	//Level box
	sf::RectangleShape levelBox;
	sf::Text levelText;
	std::string levelBoxString;

	//Exp bar
	sf::RectangleShape expBarBack;
	sf::RectangleShape expBarInner;
	sf::Text expText;
	std::string expBarString;
	float expBarMaxWidth;
	float expBarMaxHeight;

	//Hp bar
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;
	sf::Text hpText;
	std::string hpBarString;
	float hpBarMaxWidth;
	float hpBarMaxHeight;

public:
	PlayerGUI(Player* player, sf::Font& font, sf::VideoMode& vm);
	~PlayerGUI();

	//Initializers
	void initExpBar(Player* player, sf::Font& font);
	void initHpBar(Player* player, sf::Font& font);
	void initLevelBox(Player* player, sf::Font& font);

	//Functions
	void updateExpBar();
	void updateHpBar();
	void updateLevelBox();
	void update(const float& dt);

	void renderExpBar(sf::RenderTarget& target);
	void renderHpBar(sf::RenderTarget& target);
	void renderLevelBox(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

