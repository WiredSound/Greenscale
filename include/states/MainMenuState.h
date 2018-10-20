#pragma once

#include "State.h"
#include "../gui/MainMenuGui.h"

class MainMenuState : public State {
public:
	MainMenuState(StateManager &manager, sf::RenderWindow &renderWindow, sf::Font &textFont, GameSettings &gameSettings);
	void update(Input &input) override;
	void draw() override;

private:
	MainMenuGui gui;
	sf::Font &font;
	GameSettings &settings;
};