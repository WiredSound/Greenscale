#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "ChildGui.h"
#include "../debugging.h"

class GuiWindow : public ChildGui {
public:
	GuiWindow(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness);

	virtual void update(Input &input);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void mouseHover(Input &input) override;
	virtual void mouseNotHovering(Input &input) override;

protected:
	void setBackgroundColour(sf::Color colour);
	void setupBackground(sf::Color backgroundColour, sf::Color hoverBackgroundColour);
	void setBorder(sf::Color borderColour, float borderThickness);

	sf::Color backgroundColour; // The normal background colour.
	sf::Color hoverBackgroundColour; // The background colour when the mouse hovers over the window.

	sf::RectangleShape background;
};