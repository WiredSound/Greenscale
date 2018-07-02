#include "EntityListGui.h"

EntityListGui::EntityListGui(Gui &parent, TurnManager &managerTurns, sf::Font &textFont, unsigned int textSize, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness)
	: GuiWindow("Entity List", parent, position, size, origin, backgroundColour, hoverBackgroundColour, borderColour, borderThickness), turnManager(managerTurns)
{
	auto lines = std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.025f, 0.05f), sf::Vector2f(0.95f, 0.9f), sf::Vector2f(0, 0));
	lines->setNumberOfLines(8, TextLine(textFont, textSize));
	textLines = addChild(std::move(lines));
}

void EntityListGui::update(Input &input) {
	GuiWindow::update(input);

	const std::vector<std::shared_ptr<Entity>> &entities = turnManager.getCurrentEntities();

	for (int i = 0; i < entities.size(); i++) {
		const std::shared_ptr<Entity> &entity = entities[i];

		getChild<TextLinesGui>(textLines)->getLine(i).set(0, { entity->isMyTurn() ? "> " : "  ", sf::Color::White });
		getChild<TextLinesGui>(textLines)->getLine(i).set(1, { entity->getFullName(), entity->getFaction().colour });
	}
}