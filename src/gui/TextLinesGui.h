#pragma once

#include "ChildGui.h"
#include "TextLine.h"

class TextLinesGui : public ChildGui {
public:
	TextLinesGui(Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin);

	unsigned int addLine(TextLine line);
	TextLine &getLine(unsigned int index);

	unsigned int getNumberOfLines();
	void setNumberOfLines(unsigned int amount, TextLine line);

	float getLinesHeightWithoutPadding();
	float getPaddingBetweenLines();

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<TextLine> lines;
};