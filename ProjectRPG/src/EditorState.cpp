#include "stdafx.h"
#include "EditorState.h"

//Initializer functions
void EditorState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/terminal-grotesque.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initButtons()
{
}

void EditorState::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));

	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::White);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 20, 20);
}

void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(
		1 * static_cast<int>(this->stateData->gridSize),
		0 * static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->stateData->gridSize)
	);
}

void EditorState::initBackground()
{
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("config/editorstate_keybinds.ini");

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

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("EXIT", 900.f, "Exit");
}


EditorState::EditorState(StateData* state_data) :
	State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initGui();
	this->initTileMap();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;

	delete this->tileMap;
}

void EditorState::updateInput(const float& dt)
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

void EditorState::updateEditorImput(const float& dt)
{
	//add tile to tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
	}
	//remove a tile from tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	//change texture
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->getKeyTime())
	{
		if (this->textureRect.left < 320)
		{
			this->textureRect.left += 160;
		}
	}
}

void EditorState::updateButtons()
{
	//Updates all the buttons in the state
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void EditorState::updateGui()
{
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("EXIT"))
		this->endState();
}

void EditorState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused)//unpaused
	{
		this->updateGui();
		this->updateButtons();
		this->updateEditorImput(dt);
	}
	else//paused
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (target)
		target = this->window;

	this->renderButtons(*target);

	this->tileMap->render(*target);

	this->renderGui(*target);

	if (this->paused)//Pause menu render
	{
		this->pmenu->render(*target);
	}

	//REMOVE LATER !!!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 25);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << "\n" << this->textureRect.left << " " << this->textureRect.top;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
