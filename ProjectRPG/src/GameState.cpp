#include "stdafx.h"
#include "GameState.h"

//Initializers
void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(
		0,
		0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height)
	);
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height)
	);

	this->view.setCenter(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width / 2.f,
		this->stateData->gfxSettings->resolution.height / 2.f)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key_function = "";

		while (ifs >> key_function >> key)
		{
			this->keybinds[key_function] = this->supportedKeys->at(key);
		}
	}

	ifs.close();
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("assets/player/textures/player_animations.png"))
	{
		throw "ERROR::GAME_STATE::COULD NOT LOAD PLAYER TEXTURE";
	}
}

void GameState::initPlayers()
{
	this->player = new Player(960, 540, this->textures["PLAYER_SHEET"]);

}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/terminal-grotesque.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("EXIT", 900.f, "Exit");
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 20, 20, "assets/world/textures/tilesheet2.png");
	this->tileMap->loadFromFile("config/test.map");
}

//Const and Destr
GameState::GameState(StateData* state_data) :
	State(state_data)
{
	this->initDeferredRender();
	this->initView();

	this->initKeybinds();
	this->initTextures();
	this->initFonts();
	this->initPauseMenu();

	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
}

//Functions
void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key (this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("EXIT"))
	{
		this->endState();
	}
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player);
}

void GameState::update(const float& dt)
{
	this->updateMousePosition(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		this->player->update(dt);

		this->updateTileMap(dt);
	}
	else //Paused
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture);

	this->player->render(this->renderTexture);

	if (this->paused)//Pause menu render
	{
		target->setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//Final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
