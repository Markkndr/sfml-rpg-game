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
		static_cast<float>(this->stateData->gfxSettings->resolution.width),
		static_cast<float>(this->stateData->gfxSettings->resolution.height))
	);

	this->view.setCenter(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f)
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

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->font, this->stateData->gfxSettings->resolution);
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
	sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(vm, this->font);

	this->pmenu->addButton(gui::p2pX(7.8125f, vm), gui::p2pY(4.629f, vm), gui::p2pY(83.3f, vm), gui::calcCharSize(vm), "EXIT", "Exit");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER" << std::endl;
	}
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "assets/world/textures/tilesheet2.png");
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

	this->initShaders();

	this->initPlayers();
	this->initPlayerGUI();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->tileMap;
}

//Functions
void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 5.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 5.f)
	);
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->move(-1.f, 0, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->move(1.f, 0, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0, 1.f, dt);
	}

	//Stats
	this->updatePlayerStats();
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePlayerStats()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && this->getKeyTime())
	{
		this->player->gainHp(1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && this->getKeyTime())
	{
		this->player->loseHp(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
	{
		this->player->gainExp(5);
	}
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
	this->tileMap->updateCollision(this->player, dt); 
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
		this->updatePlayerGUI(dt);

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
	this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)), false);

	this->player->render(this->renderTexture, &this->core_shader, false);

	this->tileMap->renderDeferred(this->renderTexture);

	//RenderGUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused)//Pause menu render
	{
		this->pmenu->render(this->renderTexture);
	}

	//Final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
