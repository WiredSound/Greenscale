#pragma once

#include "State.h"
#include "../gui/MainMenuGui.h"

class MainMenuState : public State {
public:
	MainMenuState(sf::RenderWindow &renderWindow, sf::Font &font);
	virtual void update(Input &input) override;
	virtual void draw() override;

private:
	MainMenuGui gui;
};