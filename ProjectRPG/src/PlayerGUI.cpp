#include "stdafx.h"
#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(Player* player, sf::Font& font, sf::VideoMode& vm)
	: vm(vm)
{
	this->initExpBar(player, font);
	this->initHpBar(player, font);
	this->initLevelBox(player, font);
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::initHpBar(Player* player, sf::Font& font)
{
	float width = gui::p2pX(20.83f, this->vm);
	float height = gui::p2pY(2.778f, this->vm);
	float x = gui::p2pX(3.38f, this->vm);
	float y = gui::p2pY(1.38f, this->vm);
	this->hpBarMaxWidth = width;
	this->hpBarMaxHeight = height;

	this->player = player;
	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setPosition(sf::Vector2f(x, y));
	this->hpBarBack.setFillColor(sf::Color::Transparent);
	this->hpBarBack.setOutlineThickness(1.f); 
	this->hpBarBack.setOutlineColor(sf::Color::White);
	
	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 255));
	
	this->hpText.setFont(font); 
	this->hpText.setCharacterSize(gui::calcCharSize(this->vm, 160)); 
	this->hpText.setPosition(
		this->hpBarInner.getPosition().x + gui::p2pX(0.26f, this->vm),
		this->hpBarInner.getPosition().y + gui::p2pY(0.37f, this->vm)
	);
	this->hpText.setFillColor(sf::Color::White);
}

void PlayerGUI::initExpBar(Player* player, sf::Font& font)
{
	float width = gui::p2pX(15.625f, this->vm);
	float height = gui::p2pY(1.85f, this->vm);
	float x = gui::p2pX(3.38f, this->vm);
	float y = gui::p2pY(4.629f, this->vm);
	this->expBarMaxWidth = width;
	this->expBarMaxHeight = height;

	this->player = player;
	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setPosition(sf::Vector2f(x, y));
	this->expBarBack.setFillColor(sf::Color::Transparent);
	this->expBarBack.setOutlineThickness(1.f);
	this->expBarBack.setOutlineColor(sf::Color::White);

	this->expBarInner.setSize(sf::Vector2f(width, height));
	this->expBarInner.setPosition(this->expBarBack.getPosition());
	this->expBarInner.setFillColor(sf::Color(143, 0, 255, 255));

	this->expText.setFont(font);
	this->expText.setCharacterSize(gui::calcCharSize(this->vm, 200));
	this->expText.setPosition(
		this->expBarInner.getPosition().x + gui::p2pX(0.26f, this->vm), 
		this->expBarInner.getPosition().y + gui::p2pY(0.37f, this->vm)
	);
	this->expText.setFillColor(sf::Color::White);
}

void PlayerGUI::initLevelBox(Player* player, sf::Font& font)
{
	float width = gui::p2pX(2.86f, this->vm);
	float height = gui::p2pY(5.09f, this->vm);
	float x = gui::p2pX(0.26f, this->vm);
	float y = gui::p2pY(1.38f, this->vm);

	this->levelBox.setSize(sf::Vector2f(width, height));
	this->levelBox.setPosition(x, y);
	this->levelBox.setFillColor(sf::Color(50, 50, 50, 100));
	this->levelBox.setOutlineThickness(1.f);
	this->levelBox.setOutlineColor(sf::Color::White);

	this->levelText.setFont(font);
	this->levelText.setCharacterSize(gui::calcCharSize(this->vm, 130));
	this->levelText.setPosition(
		this->levelBox.getPosition().x + gui::p2pX(1.14f, this->vm),
		this->levelBox.getPosition().y + gui::p2pY(1.2f, this->vm)
	);
	this->levelText.setFillColor(sf::Color::White);
}

//Functions
void PlayerGUI::updateExpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->expCurrent) / static_cast<float>(this->player->getAttributeComponent()->expNext);
	this->expBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
			this->expBarMaxHeight
		)
	);
	this->expBarString = std::to_string(this->player->getAttributeComponent()->expCurrent) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expText.setString(expBarString);
}

void PlayerGUI::updateHpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->maxHp);
	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
			this->hpBarMaxHeight
		)
	);
	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->maxHp);
	this->hpText.setString(hpBarString);
}

void PlayerGUI::updateLevelBox()
{
	this->levelBoxString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelText.setString(levelBoxString);
}

void PlayerGUI::update(const float& dt)
{
	this->updateExpBar();
	this->updateHpBar();
	this->updateLevelBox();
}

//Render
void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
	target.draw(this->expBarInner);
	target.draw(this->expBarBack);
	target.draw(this->expText);
}

void PlayerGUI::renderHpBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarInner);
	target.draw(this->hpBarBack);
	target.draw(this->hpText);
}

void PlayerGUI::renderLevelBox(sf::RenderTarget& target)
{
	target.draw(this->levelBox);
	target.draw(this->levelText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderExpBar(target);
	this->renderHpBar(target);
	this->renderLevelBox(target);
}
