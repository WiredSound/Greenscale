#include "ComponentGui.h"

#define NAME_LINES 0
#define VALUE_LINES 1

ComponentGui::ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Components", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	font(textFont), gridGui(componentGridGui), okTextColour(sf::Color::Green), warningTextColour(sf::Color::Yellow), badTextColour(sf::Color::Red) {
	auto nameLines = std::make_unique<TextLines>(*this, sf::Vector2f(0.025f, 0.05f), 5);
	auto valueLines = std::make_unique<TextLines>(*this, sf::Vector2f(0.22f, 0.05f), 5);

	nameLines->addLine(TextLine(font, 16, { "Name: ", sf::Color::White }));
	nameLine = valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Description: ", sf::Color::White }));
	descriptionLine = valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Integirty: ", sf::Color::White }));
	integrityLine = valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Heat level: ", sf::Color::White }));
	heatLevelLine = valueLines->addLine(TextLine(font, 16));

	addChild(std::move(nameLines));
	addChild(std::move(valueLines));
}

void ComponentGui::update(Input &input) {
	auto &component = gridGui.getComponentHoveredOver();

	if (component) {
		// TODO: This use of dynamic_cast is probably not best practise...
		getChild<TextLines>(VALUE_LINES)->getLine(nameLine).set(0, { component->getName(), okTextColour });
		getChild<TextLines>(VALUE_LINES)->getLine(descriptionLine).set(0, { component->getDescription(), okTextColour });
		getChild<TextLines>(VALUE_LINES)->getLine(integrityLine).set(0, { std::to_string(component->getIntegrity()) + "/" + std::to_string(component->getMaxIntegrity()), okTextColour });
		getChild<TextLines>(VALUE_LINES)->getLine(heatLevelLine).set(0, { std::to_string(component->getHeatLevel()), getHeatLevelColour(*component) });
	}

	GuiWindow::update(input);
}

void ComponentGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);
}

sf::Color ComponentGui::getHeatLevelColour(Component &component) {
	if (component.getHeatLevel() >= component.getFatalHeatLevel())
		return badTextColour;
	if (component.getHeatLevel() >= component.getDangerousHeatLevel())
		return warningTextColour;
	return okTextColour;
}