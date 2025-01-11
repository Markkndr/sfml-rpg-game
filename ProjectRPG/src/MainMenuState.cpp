#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/terminal-grotesque.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buttons["GAME_STATE_BTN"] = new gui::Button(
		gui::p2pX(6.4f, vm), gui::p2pY(9.259f, vm),
		gui::p2pX(7.81f, vm), gui::p2pX(4.62f, vm),
		&this->font, "Start Game", gui::calcCharSize(vm),
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE_BTN"] = new gui::Button(
		gui::p2pX(6.4f, vm), gui::p2pY(23.15f, vm),
		gui::p2pX(6.5f, vm), gui::p2pX(4.62f, vm),
		&this->font, "Settings", gui::calcCharSize(vm),
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE_BTN"] = new gui::Button(
		gui::p2pX(6.4f, vm), gui::p2pY(37.f, vm),
		gui::p2pX(6.25f, vm), gui::p2pX(4.62f, vm),
		&this->font, "Editor", gui::calcCharSize(vm),
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE_BTN"] = new gui::Button(
		gui::p2pX(6.77f, vm), gui::p2pY(50.92f, vm),
		gui::p2pX(5.2f, vm), gui::p2pX(2.78f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), 
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::resetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();
	this->initGui();
}

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width), 
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("assets/menu/background.png"))
	{
		throw("ERROR:MAINMENUSTATE::FAILED TO LOAD BACKGROUND TEXTURE");
	}
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("config/mainmenustate_keybinds.ini");

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


MainMenuState::MainMenuState(StateData* state_data) :
	State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons()
{
	//Updates all the buttons in the state
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Start Game
	if (this->buttons["GAME_STATE_BTN"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE_BTN"]->isPressed())
	{
		this->states->push(new SettingState(this->stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE_BTN"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//Quit game
	if (this->buttons["EXIT_STATE_BTN"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();

}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	//REMOVE LATER !!!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 25 );
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
