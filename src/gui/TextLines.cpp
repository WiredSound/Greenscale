#include "TextLines.h"

TextLines::TextLines(Gui &parent, sf::Vector2f position, float padding) : ChildGui("Text Lines", parent, position, sf::Vector2f(0, 0), sf::Vector2f(0, 0)), paddingBetweenLines(padding) {}

unsigned int TextLines::addLine(TextLine line) {
	lines.push_back(line);
	return lines.size() - 1;
}

TextLine &TextLines::getLine(unsigned int index) {
	return lines[index];
}

void TextLines::update(Input &input) {
	ChildGui::update(input);

	sf::Vector2f position = getAbsolutePosition();

	for (TextLine &line : lines) {
		line.setPosition(position);

		position.y += line.getLineHeight() + paddingBetweenLines;
	}
}

void TextLines::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	ChildGui::draw(target, states);

	for (const TextLine &line : lines) {
		target.draw(line, states);
	}
}