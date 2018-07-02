#include "GameGui.h"

#include "ComponentGridGui.h"
#include "ComponentGui.h"
#include "EntityListGui.h"
#include "EntityGui.h"
#include "ConsoleGui.h"

#define COMPONENTS_TEXTURE_PATH "assets/components/components.png"

GameGui::GameGui(sf::Vector2f windowSize)
	: RootGui("Game", sf::Vector2f(0, 0), windowSize), componentsTexture(std::make_shared<sf::Texture>()) {
	componentsTexture->loadFromFile(COMPONENTS_TEXTURE_PATH);
}

void GameGui::setup(TurnManager &turnManager, sf::Font &font, unsigned int fontSize, sf::Vector2f childrenScale, sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color borderColour, int borderThickness) {
	sf::Vector2f windowSize = getAbsoluteSize();

	destroyAllChildren();

	auto entityListGui = std::make_unique<EntityListGui>(*this, turnManager, font, fontSize, sf::Vector2f(0.99f, 0.01f), sf::Vector2f(0.22f, 0.3f), sf::Vector2f(1, 0),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto componentGridGui = std::make_unique<ComponentGridGui>(*this, turnManager, componentsTexture, sf::Vector2f(0.01f, 0.755f), sf::Vector2f(0.08f, 0.08f * getAspectRatio()), sf::Vector2f(0, 1),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto componentGui = std::make_unique<ComponentGui>(*this, *componentGridGui, font, fontSize, sf::Vector2f(0.01f, 0.99f), sf::Vector2f(0.7f, 0.225f), sf::Vector2f(0, 1),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto entityGui = std::make_unique<EntityGui>(*this, font, fontSize, turnManager, sf::Vector2f(0.99, 0.99), sf::Vector2f(0.18, 0.1), sf::Vector2f(1, 1),
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	auto consoleGui = std::make_unique<ConsoleGui>(*this, font, fontSize, sf::Vector2f(0.01f, 0.01f), sf::Vector2f(0.4f, 0.3f), sf::Vector2f(0, 0), 8,
		backgroundColour, hoverBackgroundColour, borderColour, borderThickness);

	for (int i = 0; i < 10; i++) {
		consoleGui->display({ "The quick brown fox jumped over the lazy dog. This is a very long message that should, if I coded this correctly, be spread over multiple lines!", ConsoleGui::MessageType::INFO });
		consoleGui->display({ "This is a warning... Uh oh! " + std::to_string(i), ConsoleGui::MessageType::WARNING });
	}

	consoleGui->flush();

	addChild(std::move(entityListGui));
	addChild(std::move(componentGridGui));
	addChild(std::move(componentGui));
	addChild(std::move(entityGui));
	addChild(std::move(consoleGui));
}

void GameGui::update(Input &input) {
	Gui::update(input);
}