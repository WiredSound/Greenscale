#include "ComponentGui.h"

ComponentGui::ComponentGui(Gui &parent, sf::Font &textFont, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Components", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness), font(textFont), line(font, 16) {
	line.add({ "MEGA BAD...", sf::Color::Red });
	line.add({ "Wowah...", sf::Color::Cyan });
	line.setPosition(getAbsolutePosition());
}

void ComponentGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);

	target.draw(line, states);
}