#include "stdafx.h"
#include "PauseMenu.h"

//Inintializers
void PauseMenu::initBackground(sf::VideoMode& vm)
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
}

void PauseMenu::initContainer(sf::VideoMode& vm)
{
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height) - gui::p2pY(9.259f, vm)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f, 40.f);
}

//Const and Destr
PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
	:font(font)
{
	this->initBackground(vm);
	this->initContainer(vm);

	//Init text
	this->pauseText.setFont(font); 
	this->pauseText.setFillColor(sf::Color(255, 255, 255, 200)); 
	this->pauseText.setCharacterSize(gui::calcCharSize(vm));
	this->pauseText.setString("Paused"); 
	this->pauseText.setPosition(container.getPosition().x + this->container.getSize().x / 2.f - this->pauseText.getGlobalBounds().width / 2.f, container.getPosition().y + gui::p2pY(2.231f, vm));

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

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::addButton(const float width, const float height, const float y, const unsigned text_size, const std::string key, const std::string text)
{
	//height/width gui::p2pX(7.8125f, vm), gui::p2pY(4.629f, vm),

	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(x, y, width, height, &this->font, text, text_size,
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
