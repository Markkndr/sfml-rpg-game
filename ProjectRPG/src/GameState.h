#pragma once
#include "State.h"
#include "PauseMenu.h"

class GameState :
	public State
{
private:
	sf::Font font;

	PauseMenu* pmenu;

	Player* player;

	//Functions

	//Initializers
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initPauseMenu();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
