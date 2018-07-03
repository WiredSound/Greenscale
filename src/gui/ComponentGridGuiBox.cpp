#include "ComponentGridGuiBox.h"

#include "ComponentGridGui.h"

ComponentGridGuiBox::ComponentGridGuiBox(ComponentGridGui &parent, sf::Vector2u positionInGrid, sf::Vector2f position, sf::Vector2f size,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color equippedColour, sf::Color unequippedColour, float thickness)
	: GuiWindow("Component Grid Box", parent, position, size, sf::Vector2f(0, 0), backgroundColour, hoverBackgroundColour, unequippedColour, thickness),
	gridGui(parent), gridPosition(positionInGrid), equippedBorderColour(equippedColour), unequippedBorderColour(unequippedColour), borderThickness(thickness) {}

void ComponentGridGuiBox::mouseHover(Input &input) {
	GuiWindow::mouseHover(input);

	DEBUG_LOG_SPAM("Mouse over grid box: " << gridPosition.x << ", " << gridPosition.y);

	gridGui.hoveringOverGridPosition(gridPosition);

	for (sf::Mouse::Button button : input.getMouseButtonsJustPressed()) {
		if (button == sf::Mouse::Left)
			gridGui.mouseToggleHolding(gridPosition);
		if (button == sf::Mouse::Button::Right)
			gridGui.equipGridPosition(gridPosition);
		if (button == sf::Mouse::Button::Middle)
			gridGui.toggleEnableGridPosition(gridPosition);
	}
}

void ComponentGridGuiBox::equip() {
	setBorder(equippedBorderColour, borderThickness);
}
void ComponentGridGuiBox::unequip() {
	setBorder(unequippedBorderColour, borderThickness);
}