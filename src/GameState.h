#pragma once

#include <iostream>
#include <memory>
#include "State.h"
#include "map/World.h"
#include "map/MapBuilder.h"
#include "gui/GameGui.h"
#include "TurnManager.h"
#include "GameSettings.h"

class GameState : public State {
public:
	GameState(sf::RenderWindow &renderWindow, sf::Font &textFont, GameSettings &gameSettings);
	void update(Input &input) override;
	void draw() override;

private:
	World world;
	sf::Font &font;
	GameSettings &settings;
	GameGui gui;
};