#include "ComponentGridGuiBox.h"

#include "ComponentGridGui.h"

ComponentGridGuiBox::ComponentGridGuiBox(ComponentGridGui &parent, sf::Vector2u positionInGrid, sf::Vector2f position, sf::Vector2f size,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color equippedColour, sf::Color unequippedColour, float thickness)
	: GuiWindow("Component Grid Box", parent, position, size, sf::Vector2f(0, 0), backgroundColour, hoverBackgroundColour, unequippedColour, thickness),
	gridGui(parent), gridPosition(positionInGrid), equippedBorderColour(equippedColour), unequippedBorderColour(unequippedColour), borderThickness(thickness) {}

void ComponentGridGuiBox::mouseHover(sf::Vector2i position, const std::vector<sf::Mouse::Button> &mouseButtonsJustClicked) {
	GuiWindow::mouseHover(position, mouseButtonsJustClicked);

	DEBUG_LOG_SPAM("Mouse over grid box: " << gridPosition.x << ", " << gridPosition.y);

	gridGui.hoveringOverGridPosition(gridPosition);

	for (sf::Mouse::Button button : mouseButtonsJustClicked) {
		if (button == sf::Mouse::Button::Left)
			gridGui.equipGridPosition(gridPosition);
	}
}

void ComponentGridGuiBox::equip() {
	setBorder(equippedBorderColour, borderThickness);
}
void ComponentGridGuiBox::unequip() {
	setBorder(unequippedBorderColour, borderThickness);
}