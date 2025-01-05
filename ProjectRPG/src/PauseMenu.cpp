#include "stdafx.h"
#include "PauseMenu.h"

//Inintializers
void PauseMenu::initBackground(sf::RenderWindow& window)
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
}

void PauseMenu::initContainer(sf::RenderWindow& window)
{
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x) / 4.f,
			static_cast<float>(window.getSize().y) - 100.f
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 40.f);
}

//Const and Destr
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	this->initBackground(window);
	this->initContainer(window);

	//Init text
	this->pauseText.setFont(font); 
	this->pauseText.setFillColor(sf::Color(255, 255, 255, 200)); 
	this->pauseText.setCharacterSize(50); 
	this->pauseText.setString("Paused"); 
	this->pauseText.setPosition(container.getPosition().x + this->container.getSize().x / 2.f - this->pauseText.getGlobalBounds().width / 2.f, container.getPosition().y + 25);

}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Functions
const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 150;
	float height = 50;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - this->pauseText.getGlobalBounds().width / 2.f;

	this->buttons[key] = new gui::Button(x, y, width, height, &this->font, text, 30,
		sf::Color(250, 250, 250, 200), sf::Color(100, 100, 100, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto &i : this->buttons)
	{
		(i.second->render(target));
	}

	target.draw(this->pauseText);
}
