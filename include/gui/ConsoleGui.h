#pragma once

#include "GuiWindow.h"
#include "TextLinesGui.h"
#include "TextWrapper.h"

class ConsoleGui : public GuiWindow {
public:
	ConsoleGui(Gui &parent, sf::Font &textFont, unsigned int textSize, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin, unsigned int countLines,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness);

	virtual void mouseHover(Input &input) override;

	void scrollBy(int amount);
	int getMaximumScroll();

	void display(std::string text, sf::Color colour);
	void flush();
	TextLine getLine(unsigned int index);

private:
	std::vector<TextLine> lines;

	unsigned int textLinesIndex;
	unsigned lineCount;
	int scroll{ 0 };

	TextWrapper wrapper;
};