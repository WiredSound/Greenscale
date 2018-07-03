#include "ConsoleGui.h"

ConsoleGui::MessageType::MessageType(std::string typeName, sf::Color typeColour) : name(typeName), colour(typeColour) {}

const ConsoleGui::MessageType ConsoleGui::MessageType::INFO("INFO", sf::Color(0, 255, 0, 255));
const ConsoleGui::MessageType ConsoleGui::MessageType::WARNING("WARNING", sf::Color(255, 255, 0, 255));

ConsoleGui::ConsoleGui(Gui &parent, sf::Font &textFont, unsigned int textSize, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin, unsigned int countLines,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness)
	: GuiWindow("Console", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness), lineCount(countLines), wrapper(textFont, textSize)
{
	textLinesIndex = addChild(std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.01f, 0.01f), sf::Vector2f(0.9f, 0.9f), sf::Vector2f(0, 0)));
}

void ConsoleGui::mouseHover(sf::Vector2i position, const std::vector<sf::Mouse::Button> &mouseButtonsJustClicked) {
	GuiWindow::mouseHover(position, mouseButtonsJustClicked);

	for (auto &button : mouseButtonsJustClicked) {
		if (button == sf::Mouse::Button::Left) scrollDown();
		if (button == sf::Mouse::Button::Right) scrollUp();
	}
}

void ConsoleGui::scrollDown() {
	if (scroll < static_cast<int>(lines.size()) - static_cast<int>(lineCount))
		scroll++;
	flush();
}

void ConsoleGui::scrollUp() {
	if (scroll > 0)
		scroll--;
	flush();
}

void ConsoleGui::display(Message msg, bool prependMessageType) {
	if (prependMessageType) msg.text.insert(0, "(" + msg.type.name + ") - ");

	auto wrappedLines = wrapper.wrapText(msg.text, getAbsoluteSize().x, msg.type.colour);

	messages.push_back(msg);
	for (TextLine &line : wrappedLines) lines.push_back(line);
}

void ConsoleGui::flush() {
	auto *gui = getChild<TextLinesGui>(textLinesIndex);
	gui->setNumberOfLines(lineCount, TextLine(wrapper.getFont(), wrapper.getFontSize()));

	for (unsigned int i = 0; i < lineCount; i++) {
		TextLine line = getLine(i + scroll);

		gui->getLine(i).set(0, line.get(0));
	}
}

TextLine ConsoleGui::getLine(unsigned int index) {
	if (index < lines.size()) return lines[index];
	return TextLine(wrapper.getFont(), wrapper.getFontSize());
}