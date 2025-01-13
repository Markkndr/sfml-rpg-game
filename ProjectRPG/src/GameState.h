#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

class PasueMenu;
class Player;
class Enemies;
class TileMap;
class PlayerGUI;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
	public State
{
private:
	//Variables
	sf::View view;
	sf::Vector2i viewGridPos;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;

	sf::Shader core_shader;

	Player* player;
	PlayerGUI* playerGUI;

	Enemies* enemy;

	TileMap* tileMap;

	//Functions

	//Initializers
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initTextures();
	void initEnemies();
	void initPlayers();
	void initPlayerGUI();
	void initFonts();
	void initPauseMenu();
	void initShaders();
	void initTileMap();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Functions
	void updateView(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePlayerStats();
	void updateInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
