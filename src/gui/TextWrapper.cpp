#include "TextWrapper.h"

#include <sstream>

TextWrapper::TextWrapper(sf::Font &textFont, unsigned int textSize) : font(textFont), fontSize(textSize) {}

std::vector<TextLine> TextWrapper::wrapText(std::string text, float maximumWidth, sf::Color colour) {
	std::vector<TextLine> lines;
	lines.push_back(TextLine(font, fontSize));

	// Split the text into a vector of indvidual words:
	std::istringstream iss(text);
	std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	for (unsigned int wordIndex = 0; wordIndex < words.size(); wordIndex++) {
		auto &line = lines[lines.size() - 1];
		line.setColour(0, colour);

		std::string text = line.get(0).text;

		line.setText(0, text + words[wordIndex] + " ");

		if (line.getLineWidth() > maximumWidth) { // Check if the line has become two long and should therefore move onto the next line.
			line.setText(0, text); // Remove the newly added word so the line should be in bounds.

			wordIndex--;
			lines.push_back(TextLine(font, fontSize));
		}
	}

	return lines;
}

sf::Font &TextWrapper::getFont() {
	return font;
}

unsigned int TextWrapper::getFontSize() {
	return fontSize;
}