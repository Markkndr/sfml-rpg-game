#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, 
	sf::Color idleColor, sf::Color howerColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);
	this->text.setPosition(
		shape.getPosition().x + shape.getSize().x / 2 - this->text.getLocalBounds().width / 2,
		shape.getPosition().y + shape.getSize().y / 2 - this->text.getLocalBounds().height / 2
	);
	
	this->idleColor = idleColor;
	this->activeColor = activeColor;
	this->howerColor = howerColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{

}

//Functions
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

void Button::update(const sf::Vector2f mousePos)
{
	//Update the booleans for hower and pressed

	this->buttonState = BTN_IDLE;

	//Button hower
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOWER;

		//Button pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOWER:
		this->shape.setFillColor(this->howerColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
