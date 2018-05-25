#include "ComponentGui.h"

ComponentGui::ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Components", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness), font(textFont), line(font, 16), gridGui(componentGridGui) {}

void ComponentGui::update(Input &input) {
	GuiWindow::update(input);

	auto &component = gridGui.getComponentHoveredOver();

	if (component) {
		line.clear();
		line.setPosition(getAbsolutePosition() + sf::Vector2f(10, 10));
		line.add({ "Component: ", sf::Color::White });
		line.add({ component->fetchInfo().name, sf::Color::Red });
	}
}

void ComponentGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);

	target.draw(line, states);
}