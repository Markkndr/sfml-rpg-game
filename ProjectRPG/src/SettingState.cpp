#include "SettingState.h"

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/terminal-grotesque.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingState::initButtons()
{
	this->buttons["EXIT_STATE_BTN"] = new GUI::Button(123.f, 1000.f, 100.f, 30.f, &this->font, "Quit", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void SettingState::initVariables()
{
}

void SettingState::initBackground()
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

void SettingState::initKeybinds()
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

SettingState::SettingState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

SettingState::~SettingState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


//Functions
void SettingState::updateInput(const float& dt)
{
}

void SettingState::updateButtons()
{
	//Updates all the buttons in the state
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Quit game
	if (this->buttons["EXIT_STATE_BTN"]->isPressed())
	{
		this->endState();
	}
}

void SettingState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();

}

void SettingState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	if (target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	//REMOVE LATER !!!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 25);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}