#pragma once

#include <iostream>
#include <memory>
#include "State.h"
#include "map/World.h"
#include "map/MapBuilder.h"
#include "gui/GameGui.h"
#include "Camera.h"
#include "TurnManager.h"
#include "GameSettings.h"
#include "Console.h"

class GameState : public State {
public:
	GameState(sf::RenderWindow &renderWindow, sf::Font &textFont, GameSettings &gameSettings);
	void update(Input &input) override;
	void draw() override;

private:
	World world;
	Camera camera;
	GameGui gui;
	Console console;
	sf::Font &font;
	GameSettings &settings;
};