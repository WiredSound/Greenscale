#pragma once

#include "GuiWindow.h"

class GuiButton : public GuiWindow {
public:
	GuiButton(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color backgroundColourClick, sf::Color borderColour, float borderThickness);

	virtual void mouseHover(Input &input) override;
	virtual void clicked(Input &input) {}

private:
	sf::Color clickBackgroundColour;
};