#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/terminal-grotesque.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE_BTN"] = new GUI::Button(123.f, 100.f, 150.f, 50.f, &this->font, "Start Game", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE_BTN"] = new GUI::Button(123.f, 250.f, 125.f, 50.f, &this->font, "Settings", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE_BTN"] = new GUI::Button(123.f, 400.f, 120.f, 50.f, &this->font, "Editor", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE_BTN"] = new GUI::Button(123.f, 1000.f, 100.f, 30.f, &this->font, "Quit", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
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


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) :
	State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
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
		it.second->update(this->mousePosView);
	}

	//Start Game
	if (this->buttons["GAME_STATE_BTN"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE_BTN"]->isPressed())
	{
		this->states->push(new SettingState(this->window, this->supportedKeys, this->states));
	}

	//Editor
	if (this->buttons["EDITOR_STATE_BTN"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
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
