#include "TextLine.h"

#include "../debugging.h"

TextLine::TextLine(sf::Font &textFont, unsigned int size) : font(textFont), fontSize(size) {}

TextLine::TextLine(sf::Font &textFont, unsigned int size, ColourText text) : TextLine(textFont, size) {
	add(text);
}

void TextLine::setPosition(sf::Vector2f basePosition) {
	currentPosition = basePosition;

	for (sf::Text &text : texts) {
		text.setPosition(sf::Vector2f(round(currentPosition.x), round(currentPosition.y))); // The position is rounded so that the text does not appear blurry.
		currentPosition.x += text.getLocalBounds().width;
	}
}

float TextLine::getLineHeight() {
	if (texts.size() > 0) {
		return texts[0].getCharacterSize();
	}
	return fontSize;
}

float TextLine::getLineWidth() {
	float width = 0.0f;

	for (sf::Text &text : texts) {
		width += text.getLocalBounds().width;
	}

	return width;
}

void TextLine::add() {
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setPosition(currentPosition);

	texts.push_back(text);

	currentPosition.x += text.getLocalBounds().width;
}

void TextLine::add(ColourText colourText) {
	add();
	texts[texts.size() - 1].setString(colourText.text);
	texts[texts.size() - 1].setFillColor(colourText.colour);
}

void TextLine::set(unsigned int index, ColourText colourText) {
	ensureMinimumTexts(index);

	sf::Text &text = texts[index];
	text.setString(colourText.text);
	text.setFillColor(colourText.colour);
	text.setStyle(colourText.style);
}

void TextLine::setText(unsigned int index, std::string text) {
	ensureMinimumTexts(index);

	texts[index].setString(text);
}

void TextLine::setColour(unsigned int index, sf::Color colour) {
	ensureMinimumTexts(index);

	texts[index].setFillColor(colour);
}

TextLine::ColourText TextLine::get(unsigned int index) {
	ensureMinimumTexts(index);

	sf::Text &text = texts[index];

	return{
		text.getString(),
		text.getFillColor()
	};
}

void TextLine::clear() {
	texts.clear();
}

void TextLine::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (const sf::Text &text : texts) {
		target.draw(text, states);
	}
}

void TextLine::ensureMinimumTexts(unsigned int amount) {
	while (texts.size() <= amount)
		add();
}