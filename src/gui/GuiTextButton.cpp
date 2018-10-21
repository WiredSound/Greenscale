#include "gui/GuiTextButton.h"

#include <cmath>

GuiTextButton::GuiTextButton(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color backgroundColourClick, sf::Color borderColour, float borderThickness,
	sf::Font &font, unsigned textSize, std::string string, CallbackType onClick)
	: GuiButton(guiName, parent, position, size, origin, backgroundColour, hoverBackgroundColour, backgroundColourClick, borderColour, borderThickness, onClick)
{
	text.setFont(font);
	text.setCharacterSize(textSize);
	setString(string);
}

void GuiTextButton::setString(std::string string) {
	text.setString(string);
}

void GuiTextButton::update(Input &input) {
	GuiButton::update(input);

	auto size = text.getLocalBounds();
	auto pos = getAbsoluteCentre();

	text.setOrigin(sf::Vector2f(size.width / 2, size.height));
	text.setPosition(sf::Vector2f(std::round(pos.x), std::round(pos.y)));
}

void GuiTextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiButton::draw(target, states);

	target.draw(text, states);
}
