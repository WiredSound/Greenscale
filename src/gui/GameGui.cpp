#include "GameGui.h"

#include "ComponentGridGui.h"
#include "ComponentGui.h"
#include "EntityListGui.h"
#include "EntityGui.h"
#include "GuiButton.h"
#include "../TurnManager.h"

#define COMPONENTS_TEXTURE_PATH "assets/components/components.png"

GameGui::GameGui(sf::Vector2f windowSize)
	: RootGui("Game", sf::Vector2f(0, 0), windowSize), componentsTexture(std::make_shared<sf::Texture>()) {}

void GameGui::load(TurnManager &turnManager, sf::Font &font, unsigned int fontSize, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness) {
	componentsTexture->loadFromFile(COMPONENTS_TEXTURE_PATH);

	destroyAllChildren();

	auto entityListGui = std::make_unique<EntityListGui>(*this, turnManager, font, fontSize, sf::Vector2f(0.99f, 0.01f), sf::Vector2f(0.22f, 0.3f), sf::Vector2f(1.0f, 0.0f),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto componentGridGui = std::make_unique<ComponentGridGui>(*this, turnManager, componentsTexture, sf::Vector2f(0.01f, 0.99f), sf::Vector2f(0.095f, 0.095f * getAspectRatio()), sf::Vector2f(0.0f, 1.0f),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto componentGui = std::make_unique<ComponentGui>(*this, *componentGridGui, font, fontSize, sf::Vector2f(0.11f, 0.99f), sf::Vector2f(0.35f, 0.095f * getAspectRatio()), sf::Vector2f(0.0f, 1.0f),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto entityGui = std::make_unique<EntityGui>(*this, font, fontSize, turnManager, sf::Vector2f(0.76f, 0.01f), sf::Vector2f(0.18f, 0.125f), sf::Vector2f(1.0f, 0.0f),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto consoleGui = std::make_unique<ConsoleGui>(*this, font, fontSize, sf::Vector2f(0.99f, 0.99f), sf::Vector2f(0.38f, 0.3f), sf::Vector2f(1.0f, 1.0), 14,
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	addChild(std::move(entityListGui));
	addChild(std::move(componentGridGui));
	addChild(std::move(componentGui));
	addChild(std::move(entityGui));
	consoleGuiIndex = addChild(std::move(consoleGui));
}

void GameGui::update(Input &input) {
	Gui::update(input);
}

ConsoleGui *GameGui::getConsoleGui() {
	return getChild<ConsoleGui>(consoleGuiIndex);
}