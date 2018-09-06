#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "GuiButton.h"

class GuiTextButton : public GuiButton {
public:
	GuiTextButton(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color backgroundColourClick, sf::Color borderColour, float borderThickness,
		CallbackType onClick, sf::Font &font, unsigned textSize, std::string string);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setString(std::string string);

private:
	sf::Text text;
};