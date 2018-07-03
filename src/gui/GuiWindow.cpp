#include "GuiWindow.h"

GuiWindow::GuiWindow(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness) : ChildGui(guiName, parent, position, size, origin) {
	setupBackground(backgroundColour, hoverBackgroundColour);
	setBorder(borderColour, borderThickness);
}

void GuiWindow::setupBackground(sf::Color colourBackground, sf::Color colourBackgroundHover) {
	backgroundColour = colourBackground;
	hoverBackgroundColour = colourBackgroundHover;
	background.setFillColor(backgroundColour);
}

void GuiWindow::setBorder(sf::Color borderColour, float borderThickness) {
	background.setOutlineThickness(borderThickness);
	background.setOutlineColor(borderColour);
}

void GuiWindow::mouseHover(Input &input) {
	background.setFillColor(hoverBackgroundColour);
}

void GuiWindow::mouseNotHovering(Input &input) {
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