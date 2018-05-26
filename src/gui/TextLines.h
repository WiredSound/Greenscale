#pragma once

#include "ChildGui.h"
#include "TextLine.h"

class TextLines : public ChildGui {
public:
	TextLines(Gui &parent, sf::Vector2f position, float padding);

	void addLine(TextLine line);
	TextLine &getLine(unsigned int index);

	virtual void update(Input &input) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<TextLine> lines;
	float paddingBetweenLines;
};