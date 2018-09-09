#include "MoveUseModeGui.h"

MoveUseModeGui::MoveUseModeGui(Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
	sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color backgroundColourClick, sf::Color borderColour, float borderThickness,
	sf::Font &font, unsigned textSize, std::shared_ptr<PlayerController> controller, TurnManager &manager)
	: GuiTextButton("Move Use Mode Switch", parent, position, size, origin, backgroundColour, hoverBackgroundColour, backgroundColourClick,
		borderColour, borderThickness, font, textSize, ""), playerController(controller), turnManager(manager) {}

void MoveUseModeGui::update(Input &input) {
	GuiTextButton::update(input);

	std::string modeText = playerController->isInMoveMode() ? "Move" : "Use";
	setString("Mode: " + modeText);
}

void MoveUseModeGui::clicked(Input &input) {
	Entity *rawEntity = turnManager.getCurrentEntity().get();

	playerController->toggleMoveUseMode(rawEntity);
}