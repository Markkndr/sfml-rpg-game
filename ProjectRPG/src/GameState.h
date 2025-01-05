#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class GameState :
	public State
{
private:
	sf::Font font;
	PauseMenu* pmenu;
	Player* player;
	TileMap* tileMap;

	//Functions

	//Initializers
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initPauseMenu();
	void initTileMap();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Functions
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
