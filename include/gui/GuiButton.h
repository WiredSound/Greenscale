#pragma once

#include <functional>
#include "GuiWindow.h"

class GuiButton : public GuiWindow {
public:
	using CallbackType = std::function<void(Input&)>;

	GuiButton(std::string guiName, Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color backgroundColourClick, sf::Color borderColour, float borderThickness,
		CallbackType onClick = [](Input&) {});
	void mouseHover(Input &input) override;

protected:
	virtual void clicked(Input &input);

private:
	CallbackType onClickFunc;
	sf::Color clickBackgroundColour;
};