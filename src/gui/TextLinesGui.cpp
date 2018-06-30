#include "TextLinesGui.h"

TextLinesGui::TextLinesGui(Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin)
	: ChildGui("Text Lines", parent, position, size, origin) {}

unsigned int TextLinesGui::addLine(TextLine line) {
	lines.push_back(line);
	return getNumberOfLines() - 1;
}

TextLine &TextLinesGui::getLine(unsigned int index) {
	return lines[index];
}

unsigned int TextLinesGui::getNumberOfLines() {
	return static_cast<unsigned int>(lines.size());
}

void TextLinesGui::setNumberOfLines(unsigned int amount, TextLine line) {
	lines.resize(amount, line);
}

float TextLinesGui::getLinesHeightWithoutPadding() {
	float heightOfLinesWithoutPadding = 0.0f;

	for (TextLine &line : lines) {
		heightOfLinesWithoutPadding += line.getLineHeight();
	}

	return heightOfLinesWithoutPadding;
}

void TextLinesGui::update(Input &input) {
	ChildGui::update(input);

	float heightNoPadding = getLinesHeightWithoutPadding();
	float paddingHeightTotal = getAbsoluteSize().y - heightNoPadding;
	float paddingBetweenLines = paddingHeightTotal / getNumberOfLines();

	sf::Vector2f position = getAbsolutePosition();

	for (TextLine &line : lines) {
		line.setPosition(position);

		position.y += line.getLineHeight() + paddingBetweenLines;
	}
}

void TextLinesGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	ChildGui::draw(target, states);

	for (const TextLine &line : lines) {
		target.draw(line, states);
	}
}