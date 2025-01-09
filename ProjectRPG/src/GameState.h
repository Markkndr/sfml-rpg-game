#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

class PasueMenu;
class Player;
class TileMap;
class PlayerGUI;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
	public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;

	Player* player;
	PlayerGUI* playerGUI;
	TileMap* tileMap;

	//Functions

	//Initializers
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initPlayerGUI();
	void initFonts();
	void initPauseMenu();
	void initTileMap();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Functions
	void updateView(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
