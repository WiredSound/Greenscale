#include "ComponentGui.h"

ComponentGui::ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Components", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	font(textFont), gridGui(componentGridGui), okTextColour(sf::Color::Green), warningTextColour(sf::Color::Yellow), badTextColour(sf::Color::Red) {
	auto nameLines = std::make_unique<TextLines>(*this, sf::Vector2f(0.025f, 0.05f), 5);
	auto valueLines = std::make_unique<TextLines>(*this, sf::Vector2f(0.23f, 0.05f), 5);

	nameLines->addLine(TextLine(font, 16, { "Name:", sf::Color::White }));
	nameLine = valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Description:", sf::Color::White }));
	descriptionLine = valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Integrity:", sf::Color::White }));
	integrityLine = valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Heat level:", sf::Color::White }));
	heatLevelLine = valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Passive power drain:", sf::Color::White }));
	passivePowerDrainLine = valueLines->addLine(TextLine(font, 16));

	propertyNameLines = addChild(std::move(nameLines));
	propertyValueLines = addChild(std::move(valueLines));
}

void ComponentGui::update(Input &input) {
	auto &component = gridGui.getComponentHoveredOver();

	if (component) {
		// TODO: This use of dynamic_cast is probably not best practise...
		getChild<TextLines>(propertyValueLines)->getLine(nameLine).set(0, { component->getName(), okTextColour });
		getChild<TextLines>(propertyValueLines)->getLine(descriptionLine).set(0, { component->getDescription(), okTextColour });
		getChild<TextLines>(propertyValueLines)->getLine(integrityLine).set(0, { std::to_string(component->getIntegrity()) + "/" + std::to_string(component->getMaxIntegrity()), okTextColour });
		getChild<TextLines>(propertyValueLines)->getLine(heatLevelLine).set(0, { std::to_string(component->getHeatLevel()), getHeatLevelColourText(*component).second });
		getChild<TextLines>(propertyValueLines)->getLine(heatLevelLine).set(1, { " (" + getHeatLevelColourText(*component).first + ")", getHeatLevelColourText(*component).second });
		getChild<TextLines>(propertyValueLines)->getLine(passivePowerDrainLine).set(0, { std::to_string(component->getPassivePowerDrain()) + " per turn", warningTextColour });
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