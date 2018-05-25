#pragma once

#include "GuiWindow.h"
class ComponentGridGui;

class ComponentGridGuiBox : public GuiWindow {
public:
	ComponentGridGuiBox(ComponentGridGui &parent, sf::Vector2u positionInGrid, sf::Vector2f position, sf::Vector2f size, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour);

	virtual void mouseHover(sf::Vector2i position, const std::vector<sf::Mouse::Button> &mouseButtonsJustClicked) override;

	const sf::Vector2u gridPosition;

private:
	ComponentGridGui &gridGui;
};