#pragma once

#include "ChildGui.h"
#include "TextLine.h"

class TextLines : public ChildGui {
public:
	TextLines(Gui &parent, sf::Vector2f position, float padding);

	unsigned int addLine(TextLine line);
	TextLine &getLine(unsigned int index);
	void numberOfLines(unsigned int amount, TextLine line);

	sf::Vector2f getDimensions();

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<TextLine> lines;

private:
	float paddingBetweenLines;
};