#include "GuiWindow.h"

GuiWindow::GuiWindow(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness) : ChildGui(guiName, parent, position, size, origin) {
	setupBackground(backgroundColour, hoverBackgroundColour, borderColour, borderThickness);
}

void GuiWindow::setupBackground(sf::Color colourBackground, sf::Color colourBackgroundHover, sf::Color borderColour, int borderThickness) {
	backgroundColour = colourBackground;
	hoverBackgroundColour = colourBackgroundHover;

	background.setFillColor(backgroundColour);
	background.setOutlineThickness(borderThickness);
	background.setOutlineColor(borderColour);
}

void GuiWindow::mouseHover(sf::Vector2i position, const std::vector<sf::Mouse::Button> &mouseButtonsJustClicked) {
	background.setFillColor(hoverBackgroundColour);
}

void GuiWindow::mouseNotHovering(sf::Vector2i position) {
	background.setFillColor(backgroundColour);
}

void GuiWindow::update(Input &input) {
	background.setPosition(getAbsolutePosition());
	background.setSize(sf::Vector2f(getAbsoluteSize().x, getAbsoluteSize().y));

	Gui::update(input);
}

void GuiWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(background, states);
	
	Gui::draw(target, states);
}