#include "ComponentGui.h"

#include <cmath>

ComponentGui::ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, unsigned int fontSize, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness)
	: GuiWindow("Components", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	font(textFont), textSize(fontSize), gridGui(componentGridGui), okTextColour(sf::Color::Green), warningTextColour(sf::Color::Yellow), badTextColour(sf::Color::Red), wrapper(textFont, fontSize)
{
	auto lines = std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.01f, 0.01f), sf::Vector2f(0.95f, 0.9f), sf::Vector2f(0.0f, 0.0f));

	nameLineIndex = lines->addLine(TextLine(font, textSize));
	descriptionLineIndex = lines->addLine(TextLine(font, textSize));

	linesIndex = addChild(std::move(lines));
}

void ComponentGui::update(Input &input) {
	auto &component = gridGui.getComponentHoveredOver();

	if (component) {
		auto lines = getChild<TextLinesGui>(linesIndex);

		lines->getLine(nameLineIndex).set(0, { component->getName(), sf::Color::White, sf::Text::Style::Underlined | sf::Text::Style::Bold });
		lines->getLine(nameLineIndex).set(1, { " (integrity: ", sf::Color::White, sf::Text::Style::Regular });
		lines->getLine(nameLineIndex).set(2, { std::to_string(component->getIntegrity()) + "/" + std::to_string(component->getMaxIntegrity()), okTextColour, sf::Text::Style::Bold });
		lines->getLine(nameLineIndex).set(3, { " heat: ", sf::Color::White, sf::Text::Style::Regular });
		lines->getLine(nameLineIndex).set(4, { std::to_string(component->getHeatLevel()), getHeatLevelColourText(*component).second, sf::Text::Style::Bold });
		lines->getLine(nameLineIndex).set(5, { ")", sf::Color::White, sf::Text::Style::Regular });

		auto wrappedLines = wrapper.wrapText(component->getDescription(), lines->getAbsoluteSize().x);

		lines->setNumberOfLines(1 + wrappedLines.size(), TextLine(font, textSize));

		for (unsigned int i = 0; i < wrappedLines.size(); i++) {
			auto wrappedLine = wrappedLines[i].get(0);
			lines->getLine(i + 1).set(0, { wrappedLine.text, wrappedLine.colour, sf::Text::Style::Italic });
		}
	}

	GuiWindow::update(input);
}

void ComponentGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);
}

std::pair<std::string, sf::Color> ComponentGui::getHeatLevelColourText(Component &component) {
	if (component.getHeatLevel() >= component.getFatalHeatLevel())
		return std::make_pair("fatal", badTextColour);
	if (component.getHeatLevel() >= component.getDangerousHeatLevel())
		return std::make_pair("dangerous", warningTextColour);
	return std::make_pair("ok", okTextColour);
}

sf::Color ComponentGui::colourBasedOnSign(int value, sf::Color positiveColour, sf::Color zeroColour, sf::Color negativeColour) {
	if (value > 0) return positiveColour;
	if (value < 0) return negativeColour;
	return zeroColour;
}