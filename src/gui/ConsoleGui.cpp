#include "ConsoleGui.h"

ConsoleGui::MessageType::MessageType(std::string typeName, sf::Color typeColour) : name(typeName), colour(typeColour) {}

const ConsoleGui::MessageType ConsoleGui::MessageType::INFO("INFO", sf::Color(0, 255, 0, 255));
const ConsoleGui::MessageType ConsoleGui::MessageType::WARNING("WARNING", sf::Color(255, 255, 0, 255));

ConsoleGui::ConsoleGui(Gui &parent, sf::Font &textFont, unsigned int textSize, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin, unsigned int countLines,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness)
	: GuiWindow("Console", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	lineCount(countLines), font(textFont), fontSize(textSize)
{
	textLinesIndex = addChild(std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.01f, 0.01f), sf::Vector2f(0.9f, 0.9f), sf::Vector2f(0, 0)));
}

void ConsoleGui::display(Message msg, bool prependMessageType) {
	if (prependMessageType) msg.text.insert(0, "(" + msg.type.name + ") - ");
	messages.push_back(msg);

	scroll++;
}

void ConsoleGui::flush() {
	// First calculate line wrapping and store the results in lines:

	std::vector<TextLine> lines;

	unsigned int messageIndex = 0 < scroll < messages.size() ? scroll : messages.size();

	while (lines.size() < lineCount && messageIndex < messages.size()) {
		auto &messageLines = wrapMessage(messages[messageIndex]);

		for (TextLine &messageLine : messageLines)
			lines.push_back(messageLine);

		messageIndex++;
	}

	// Take the wrapped text from lines and actually display it on the GUI:

	auto *gui = getChild<TextLinesGui>(textLinesIndex);
	gui->setNumberOfLines(lineCount, TextLine(font, fontSize));

	for (unsigned int i = 0; i < lines.size(); i++) {
		gui->getLine(i).setText(0, lines[i].get(0).text);
		gui->getLine(i).setColour(0, lines[i].get(0).colour);
	}
}

std::vector<TextLine> ConsoleGui::wrapMessage(ConsoleGui::Message msg) {
	std::vector<TextLine> lines;
	lines.push_back(TextLine(font, fontSize));

	// Split the text into a vector of indvidual words:
	std::istringstream iss(msg.text);
	std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	for (unsigned int wordIndex = 0; wordIndex < words.size(); wordIndex++) {
		auto &line = lines[lines.size() - 1];
		line.setColour(0, msg.type.colour);

		std::string text = line.get(0).text;

		line.setText(0, text + words[wordIndex] + " ");

		if (line.getLineWidth() > getAbsoluteSize().x) { // Check if the line has become two long and should therefore move onto the next line.
			line.setText(0, text); // Remove the newly added word so the line should be in bounds.

			wordIndex--;
			lines.push_back(TextLine(font, fontSize));
		}
	}

	return lines;
}