#include "ComponentGui.h"

#define NAME_LINES 0
#define VALUE_LINES 1

ComponentGui::ComponentGui(Gui &parent, ComponentGridGui &componentGridGui, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Components", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	font(textFont), gridGui(componentGridGui) {
	auto nameLines = std::make_unique<TextLines>(*this, sf::Vector2f(0.025f, 0.05f), 5);
	auto valueLines = std::make_unique<TextLines>(*this, sf::Vector2f(0.22f, 0.05f), 5);

	nameLines->addLine(TextLine(font, 16, { "Name: ", sf::Color::White }));
	valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Description: ", sf::Color::White }));
	valueLines->addLine(TextLine(font, 16));

	nameLines->addLine(TextLine(font, 16, { "Heat: ", sf::Color::White }));

	addChild(std::move(nameLines));
	addChild(std::move(valueLines));
}

void ComponentGui::update(Input &input) {
	auto &component = gridGui.getComponentHoveredOver();

	if (component) {
		auto info = component->fetchInfo();

		// TODO: This use of dynamic_cast is probably not best practise...
		getChild<TextLines>(VALUE_LINES)->getLine(0).clear();
		getChild<TextLines>(VALUE_LINES)->getLine(0).add({ info.name, sf::Color::Red });

		getChild<TextLines>(VALUE_LINES)->getLine(1).clear();
		getChild<TextLines>(VALUE_LINES)->getLine(1).add({ info.description, sf::Color::Red });
	}

	GuiWindow::update(input);
}

void ComponentGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);
}