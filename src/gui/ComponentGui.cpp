#include "ComponentGui.h"

#include <cmath>

ComponentGui::ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, unsigned int fontSize, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Components", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	font(textFont), gridGui(componentGridGui), okTextColour(sf::Color::Green), warningTextColour(sf::Color::Yellow), badTextColour(sf::Color::Red) {
	auto nameLines = std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.025f, 0.05f), sf::Vector2f(0.95, 0.9), sf::Vector2f(0, 0));
	auto valueLines = std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.26f, 0.05f), sf::Vector2f(0.95, 0.9), sf::Vector2f(0, 0));

	nameLines->addLine(TextLine(font, fontSize, { "Name:", sf::Color::White }));
	nameLine = valueLines->addLine(TextLine(font, fontSize));

	nameLines->addLine(TextLine(font, fontSize, { "Description:", sf::Color::White }));
	descriptionLine = valueLines->addLine(TextLine(font, fontSize));

	nameLines->addLine(TextLine(font, fontSize, { "Integrity:", sf::Color::White }));
	integrityLine = valueLines->addLine(TextLine(font, fontSize));

	nameLines->addLine(TextLine(font, fontSize, { "Heat level:", sf::Color::White }));
	heatLevelLine = valueLines->addLine(TextLine(font, fontSize));

	nameLines->addLine(TextLine(font, fontSize, { "Passive power:", sf::Color::White }));
	passivePowerLine = valueLines->addLine(TextLine(font, fontSize));

	nameLines->addLine(TextLine(font, fontSize, { "Use power:", sf::Color::White }));
	usePowerLine = valueLines->addLine(TextLine(font, fontSize));

	propertyNameLines = addChild(std::move(nameLines));
	propertyValueLines = addChild(std::move(valueLines));
}

void ComponentGui::update(Input &input) {
	auto &component = gridGui.getComponentHoveredOver();

	if (component) {
		// TODO: This use of dynamic_cast is probably not best practise...
		getChild<TextLinesGui>(propertyValueLines)->getLine(nameLine).set(0, { component->getName(), okTextColour });

		getChild<TextLinesGui>(propertyValueLines)->getLine(descriptionLine).set(0, { component->getDescription(), okTextColour });

		getChild<TextLinesGui>(propertyValueLines)->getLine(integrityLine).set(0, { std::to_string(component->getIntegrity()) + "/" + std::to_string(component->getMaxIntegrity()), okTextColour });

		getChild<TextLinesGui>(propertyValueLines)->getLine(heatLevelLine).set(0, { std::to_string(component->getHeatLevel()), getHeatLevelColourText(*component).second });
		getChild<TextLinesGui>(propertyValueLines)->getLine(heatLevelLine).set(1, { " (" + getHeatLevelColourText(*component).first + ")", getHeatLevelColourText(*component).second });

		getChild<TextLinesGui>(propertyValueLines)->getLine(passivePowerLine).set(0, { std::to_string(component->getPassivePower()) + " per turn",
			colourBasedOnSign(component->getPassivePower(), okTextColour, warningTextColour, badTextColour) });

		getChild<TextLinesGui>(propertyValueLines)->getLine(usePowerLine).set(0, { std::to_string(component->getUsePower()) + " on use",
			colourBasedOnSign(component->getUsePower(), okTextColour, warningTextColour, badTextColour) });
	}

	//sizeFromParent.y = absoluteSizeToRelative(getChild<TextLinesGui>(propertyValueLines)->getDimensions()).y * 1.1f;

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