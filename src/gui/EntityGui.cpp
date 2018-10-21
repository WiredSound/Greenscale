#include "gui/EntityGui.h"

EntityGui::EntityGui(Gui &parent, sf::Font &textFont, unsigned int fontSize, TurnManager &manager, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness)
	: GuiWindow("Entity Info", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness), font(textFont), turnManager(manager) {
	auto lines = std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.025f, 0.05f), sf::Vector2f(0.95f, 0.9f), sf::Vector2f(0, 0));

	nameLine = lines->addLine(TextLine(font, fontSize, { "Name: ", sf::Color::White }));
	integrityLine = lines->addLine(TextLine(font, fontSize, { "Integrity: ", sf::Color::White }));
	powerLine = lines->addLine(TextLine(font, fontSize, { "Power: ", sf::Color::White }));
	movementRangeLine = lines->addLine(TextLine(font, fontSize, { "Movement Range: ", sf::Color::White }));

	entityInfoLines = addChild(std::move(lines));
}

void EntityGui::update(Input &input) {
	GuiWindow::update(input);

	auto &entity = turnManager.getCurrentEntity();
	auto lines = getChild<TextLinesGui>(entityInfoLines);

	lines->getLine(nameLine).set(1, { entity->getFullName(), sf::Color::White });

	unsigned int integrity = entity->getIntegrity();
	unsigned int maxIntegrity = entity->getMaxIntegrity();
	lines->getLine(integrityLine).set(1, { std::to_string(integrity) + "/" + std::to_string(maxIntegrity), colourBasedOnPercentage(integrity, maxIntegrity) });

	unsigned int power = entity->getPowerLevel();
	unsigned int maxPower = entity->getMaxPowerStorage();
	lines->getLine(powerLine).set(1, { std::to_string(power) + "/" + std::to_string(maxPower), colourBasedOnPercentage(power, maxPower) });

	unsigned int movementRange = entity->getMovementRange();
	lines->getLine(movementRangeLine).set(1, { std::to_string(movementRange), sf::Color::Green });
}

sf::Color EntityGui::colourBasedOnPercentage(unsigned int integrity, unsigned int maxIntegrity) {
	float fraction = 0.0f;

	if (maxIntegrity > 0)
		fraction = static_cast<float>(integrity) / static_cast<float>(maxIntegrity);

	if (fraction <= 0.25) return sf::Color::Red;
	if (fraction <= 0.75) return sf::Color::Yellow;
	return sf::Color::Green;
}
