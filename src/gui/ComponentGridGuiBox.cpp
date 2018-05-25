#include "ComponentGridGuiBox.h"

#include "ComponentGridGui.h"

ComponentGridGuiBox::ComponentGridGuiBox(ComponentGridGui &parent, sf::Vector2u positionInGrid, sf::Vector2f position, sf::Vector2f size, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour)
	: GuiWindow("Component Grid Box", parent, position, size, sf::Vector2f(0, 0), backgroundColour, hoverBackgroundColour, borderColour, 1), gridGui(parent), gridPosition(positionInGrid) {}

void ComponentGridGuiBox::mouseHover(sf::Vector2i position, const std::vector<sf::Mouse::Button> &mouseButtonsJustClicked) {
	GuiWindow::mouseHover(position, mouseButtonsJustClicked);

	gridGui.hoverGridPosition = gridPosition;
}