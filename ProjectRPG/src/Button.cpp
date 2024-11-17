#include "Button.h"

GUI::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned characte_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);

	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(characte_size);
	this->text.setPosition(
		shape.getPosition().x + shape.getSize().x / 2 - this->text.getGlobalBounds().width / 2,
		shape.getPosition().y + shape.getSize().y / 2 - this->text.getGlobalBounds().height / 2
	);
	
	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->activeColor = active_color;
	this->hoverColor = hover_color;
}

GUI::Button::~Button()
{

}

//Functions
const bool GUI::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

void GUI::Button::update(const sf::Vector2f& mousePos)
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
		this->text.setFillColor(this->textIdleColor);
		break;
	case BTN_HOWER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
