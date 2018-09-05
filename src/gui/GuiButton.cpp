#include "GuiButton.h"

GuiButton::GuiButton(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color backgroundColourClick, sf::Color borderColour, float borderThickness)
	: GuiWindow(guiName, parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness), clickBackgroundColour(backgroundColourClick) {}

void GuiButton::mouseHover(Input &input) {
	GuiWindow::mouseHover(input);

	if (input.isMouseButtonHeld(sf::Mouse::Button::Left))
		setBackgroundColour(clickBackgroundColour);

	if (input.isMouseButtonJustPressed(sf::Mouse::Button::Left)) clicked(input);
}