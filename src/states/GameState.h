#pragma once

#include <iostream>
#include <memory>
#include "State.h"
#include "../map/World.h"
#include "../map/MapBuilder.h"
#include "../gui/GameGui.h"
#include "../Camera.h"
#include "../TurnManager.h"
#include "../GameSettings.h"
#include "../Console.h"

/**
 * This is where the bulk of the program takes place. GameState overrides both the State::update and State::draw methods of its superclass. It also takes references to the window, text font and game settings
 * in its constructor with the first passed to the super constructor and the latter two kept as private members. The constructor is also tasked with setting up the GameGui and ensuring the instance of
 * the Console class has a reference to GUI console window. The game World and Camera are handled by this class as well.
 */
class GameState : public State {
public:
	GameState(StateManager &manager, sf::RenderWindow &renderWindow, sf::Font &textFont, GameSettings &gameSettings);
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