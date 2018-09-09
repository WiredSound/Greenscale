#include "GuiButton.h"

GuiButton::GuiButton(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color backgroundColourClick, sf::Color borderColour, float borderThickness, CallbackType onClick)
	: GuiWindow(guiName, parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness), clickBackgroundColour(backgroundColourClick),
	onClickFunc(onClick) {}

void GuiButton::mouseHover(Input &input) {
	if (input.isMouseButtonHeld(sf::Mouse::Button::Left))
		setBackgroundColour(clickBackgroundColour);

	GuiWindow::mouseHover(input);

	if (input.isMouseButtonJustPressed(sf::Mouse::Button::Left)) clicked(input);
}

void GuiButton::clicked(Input &input) {
	onClickFunc(input);
}