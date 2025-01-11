#pragma once

#include "Gui.h"

class Gui;

class PauseMenu
{
private:
	//Variables
	sf::Font& font;
	sf::Text pauseText;
	
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	//Initializers
	void initBackground(sf::VideoMode& vm);
	void initContainer(sf::VideoMode& vm);

public:
	PauseMenu(sf::VideoMode& vm, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void update(const sf::Vector2i& mousePosWindow);
	void addButton(const float width, const float height, const float y, const unsigned text_size, const std::string key, const std::string text);
	void render(sf::RenderTarget& target);
};
