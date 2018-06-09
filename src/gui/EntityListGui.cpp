#include "EntityListGui.h"

EntityListGui::EntityListGui(Gui &parent, TurnManager &managerTurns, sf::Font &textFont, unsigned int sizeText, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Entity List", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	turnManager(managerTurns), font(textFont), textSize(sizeText) {}

void EntityListGui::update(Input &input) {
	GuiWindow::update(input);

	const std::vector<std::shared_ptr<Entity>> &entities = turnManager.getCurrentEntities();

	for (int i = 0; i < entities.size(); i++) {
		const std::shared_ptr<Entity> &entity = entities[i];

		while (i >= lines.size()) { // TODO: Set up to use TextLines class instead.
			sf::Text text;
			text.setFont(font);
			text.setCharacterSize(textSize);
			lines.push_back(text);
		}

		lines[i].setString((entity->isMyTurn() ? "> " : "  ") + entity->name);
		lines[i].setFillColor(entity->getFaction().colour);
		lines[i].setPosition(getAbsolutePosition().x + 8, getAbsolutePosition().y + (i * (textSize * 1.2f)) + 8);
	}
}

void EntityListGui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	GuiWindow::draw(target, states);

	for (const sf::Text &line : lines)
		target.draw(line, states);
}