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
	void initBackground(sf::RenderWindow& window);
	void initContainer(sf::RenderWindow& window);

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void update(const sf::Vector2i& mousePosWindow);
	void addButton(const std::string key, float y, const std::string text);
	void render(sf::RenderTarget& target);
};
