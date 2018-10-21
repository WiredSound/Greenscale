#include "gui/GameGui.h"

#include "gui/ComponentGridGui.h"
#include "gui/ComponentGui.h"
#include "gui/EntityListGui.h"
#include "gui/EntityGui.h"
#include "gui/MoveUseModeGui.h"
#include "TurnManager.h"

#define COMPONENTS_TEXTURE_PATH "assets/components/components.png"

GameGui::GameGui(sf::Vector2f windowSize)
	: RootGui("Game", sf::Vector2f(0, 0), windowSize), componentsTexture(std::make_shared<sf::Texture>()), fps(sf::milliseconds(2000)) {}

void GameGui::load(TurnManager &turnManager, std::shared_ptr<PlayerController> playerController,
	sf::Font &font, unsigned int fontSize, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, float borderThickness) {
	componentsTexture->loadFromFile(COMPONENTS_TEXTURE_PATH);

	destroyAllChildren();

	float gridHeight = 0.095f * getAspectRatio();

	auto entityListGui = std::make_unique<EntityListGui>(*this, turnManager, font, fontSize, sf::Vector2f(0.99f, 0.01f), sf::Vector2f(0.22f, 0.3f), sf::Vector2f(1.0f, 0.0f),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto componentGridGui = std::make_unique<ComponentGridGui>(*this, turnManager, componentsTexture, sf::Vector2f(0.01f, 0.99f), sf::Vector2f(0.095f, gridHeight), sf::Vector2f(0.0f, 1.0f),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto componentGui = std::make_unique<ComponentGui>(*this, *componentGridGui, font, fontSize, sf::Vector2f(0.11f, 0.99f), sf::Vector2f(0.35f, gridHeight), sf::Vector2f(0.0f, 1.0f),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto entityGui = std::make_unique<EntityGui>(*this, font, fontSize, turnManager, sf::Vector2f(0.76f, 0.01f), sf::Vector2f(0.18f, 0.125f), sf::Vector2f(1.0f, 0.0f),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto consoleGui = std::make_unique<ConsoleGui>(*this, font, fontSize, sf::Vector2f(0.99f, 0.99f), sf::Vector2f(0.38f, 0.3f), sf::Vector2f(1.0f, 1.0), 14,
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto fpsGui = std::make_unique<TextLinesGui>(*this, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.2f, 0.1f), sf::Vector2f(0.0f, 0.0f));
	fpsGui->addLine(TextLine(font, fontSize, { "FPS: ", sf::Color::Yellow }));

	auto moveUseSwitchGui = std::make_unique<MoveUseModeGui>(*this, sf::Vector2f(0.01f, 0.98f - gridHeight), sf::Vector2f(0.08f, 0.04f), sf::Vector2f(0.0f, 1.0f),
		backgroundColour, hoverBackgroundColour, sf::Color::Black, borderColour, borderThickness, font, fontSize, playerController, turnManager);

	addChild(std::move(entityListGui));
	addChild(std::move(componentGridGui));
	addChild(std::move(componentGui));
	addChild(std::move(entityGui));
	consoleGuiIndex = addChild(std::move(consoleGui));
	fpsGuiIndex = addChild(std::move(fpsGui));
	addChild(std::move(moveUseSwitchGui));
}

void GameGui::update(Input &input) {
	Gui::update(input);

	fps.update();
	getChild<TextLinesGui>(fpsGuiIndex)->getLine(0).set(1, { std::to_string(fps.get()), sf::Color::Yellow });
}

ConsoleGui *GameGui::getConsoleGui() {
	return getChild<ConsoleGui>(consoleGuiIndex);
}
