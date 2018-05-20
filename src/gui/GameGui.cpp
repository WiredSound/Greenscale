#include "GameGui.h"

#include "ComponentGridGui.h"
#include "ComponentGui.h"
#include "EntityListGui.h"

#define COMPONENTS_TEXTURE_PATH "assets/components/components.png"

GameGui::GameGui(sf::Vector2f windowSize)
	: RootGui("Game", sf::Vector2f(0, 0), windowSize), componentsTexture(std::make_shared<sf::Texture>()) {
	componentsTexture->loadFromFile(COMPONENTS_TEXTURE_PATH);
}

void GameGui::setup(TurnManager &turnManager, sf::Font &font, sf::Vector2f childrenScale, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness) {
	sf::Vector2f windowSize = getAbsoluteSize();

	destroyAllChildren();

	// TODO: Position all GUI elements as a fraction of their parent rather than individual pixels?

	addChild(std::make_unique<EntityListGui>(*this, turnManager, font, 15, sf::Vector2f(0.99f, 0.01f), sf::Vector2f(0.22f, 0.3f), sf::Vector2f(1, 0),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness));

	addChild(std::make_unique<ComponentGui>(*this, font, sf::Vector2f(0.01f, 0.99f), sf::Vector2f(0.5f, 0.25f), sf::Vector2f(0, 1),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness));

	addChild(std::make_unique<ComponentGridGui>(*this, turnManager, componentsTexture, sf::Vector2f(16, 16), sf::Vector2f(0.01f, 0.73f), sf::Vector2f(0.08f, 0.08f * getAspectRatio()), sf::Vector2f(0, 1),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness));
}

void GameGui::update(Input &input) {
	Gui::update(input);
}