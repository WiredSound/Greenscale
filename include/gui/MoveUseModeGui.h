#pragma once

#include "GuiTextButton.h"
#include "../TurnManager.h"
#include "../entities/controllers/PlayerController.h"

class MoveUseModeGui : public GuiTextButton {
public:
	MoveUseModeGui(Gui &parent, sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin,
		sf::Color backgroundColour, sf::Color hoverBackgroundColour, sf::Color backgroundColourClick, sf::Color borderColour, float borderThickness,
		sf::Font &font, unsigned textSize, std::shared_ptr<PlayerController> controller, TurnManager &manager);

	virtual void update(Input &input) override;

protected:
	void clicked(Input &input) override;

private:
	std::shared_ptr<PlayerController> playerController;
	TurnManager &turnManager;
};