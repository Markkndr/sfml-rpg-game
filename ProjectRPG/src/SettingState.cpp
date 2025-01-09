#include "stdafx.h"
#include "SettingState.h"

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("assets/fonts/terminal-grotesque.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingState::initGui()
{
	this->buttons["EXIT_STATE_BTN"] = new gui::Button(100.f, 1000.f, 200.f, 50.f, &this->font, "Back", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY_SETTINGS_BTN"] = new gui::Button(100.f, 800.f, 200.f, 50.f, &this->font, "Apply", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(100.f, 100.f, 200.f, 50.f, font, modes_str.data(), static_cast<unsigned int>(modes_str.size()), 0);
}

void SettingState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(1000.f, 300.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));


	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n"
	);
}

void SettingState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
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

SettingState::SettingState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingState::~SettingState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}


//Functions
void SettingState::updateInput(const float& dt)
{
}

void SettingState::updateGui(const float& dt)
{
	//Updates all the gui elements in the state and handle their functionality

	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
	//Button functionality

	//Dropdownlists
	for (auto& it2 : this->dropDownLists)
	{
		it2.second->update(this->mousePosWindow, dt);
	}
	//Dropdownlists funtionality
	
	//Apply Settings
	if (this->buttons["APPLY_SETTINGS_BTN"]->isPressed())
	{
		//TEST
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}
	//Quit game
	if (this->buttons["EXIT_STATE_BTN"]->isPressed())
	{
		this->endState();
	}
}

void SettingState::update(const float& dt)
{
	//Settings
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateGui(dt);

}

void SettingState::renderGui(sf::RenderTarget& target)
{
	//Buttons
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
	//Dropdownlists
	for (auto& it2 : this->dropDownLists)
	{
		it2.second->render(target);
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	if (target)
		target = this->window;

	target->draw(this->background);

	target->draw(this->optionsText);

	this->renderGui(*target);


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