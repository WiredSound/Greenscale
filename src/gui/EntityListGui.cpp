#include "EntityListGui.h"

EntityListGui::EntityListGui(Gui &parent, TurnManager &managerTurns, sf::Font &textFont, unsigned int sizeText, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Entity List", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness),
	turnManager(managerTurns), font(textFont), textSize(sizeText) {
	textLines = addChild(std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.025f, 0.05f), sf::Vector2f(0.95f, 0.9f), sf::Vector2f(0, 0)));
}

void EntityListGui::update(Input &input) {
	GuiWindow::update(input);

	const std::vector<std::shared_ptr<Entity>> &entities = turnManager.getCurrentEntities();

	getChild<TextLinesGui>(textLines)->setNumberOfLines(entities.size(), TextLine(font, textSize));

	for (int i = 0; i < entities.size(); i++) {
		const std::shared_ptr<Entity> &entity = entities[i];

		getChild<TextLinesGui>(textLines)->getLine(i).set(0, { entity->isMyTurn() ? "> " : "  ", sf::Color::White });
		getChild<TextLinesGui>(textLines)->getLine(i).set(1, { entity->name, entity->getFaction().colour });
	}
}