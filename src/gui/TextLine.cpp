#include "TextLine.h"

TextLine::TextLine(sf::Font &textFont, unsigned int size) : font(textFont), fontSize(size) {}

TextLine::TextLine(sf::Font &textFont, unsigned int size, ColourText text) : TextLine(textFont, size) {
	add(text);
}

void TextLine::setPosition(sf::Vector2f basePosition) {
	currentPosition = basePosition;

	for (sf::Text &text : texts) {
		text.setPosition(currentPosition);
		currentPosition.x += text.getLocalBounds().width;
	}
}

float TextLine::getLineHeight() {
	return texts[0].getLocalBounds().height;
}

void TextLine::add(ColourText colourText) {
	sf::Text text;
	text.setString(colourText.text);
	text.setFillColor(colourText.colour);
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setPosition(currentPosition);

	texts.push_back(text);

	currentPosition.x += text.getLocalBounds().width;
}

void TextLine::clear() {
	texts.clear();
}

void TextLine::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (const sf::Text &text : texts) {
		target.draw(text, states);
	}
}