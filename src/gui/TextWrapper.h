#pragma once

#include <SFML/Graphics/Font.hpp>
#include "TextLine.h"

class TextWrapper {
public:
	TextWrapper(sf::Font &textFont, unsigned int textSize);
	std::vector<TextLine> wrapText(std::string text, float maximumWidth, sf::Color colour = sf::Color(255, 255, 255, 255));

	sf::Font &getFont();
	unsigned int getFontSize();

private:
	sf::Font &font;
	unsigned int fontSize;
};