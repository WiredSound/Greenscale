#pragma once

#include <iostream>
#include <memory>
#include "State.h"
#include "map/GameMap.h"
#include "map/MapBuilder.h"
#include "gui/GameGui.h"
#include "TurnManager.h"

class GameState : public State {
public:
	GameState(sf::RenderWindow &renderWindow, sf::Font &textFont);
	void update(Input &input) override;
	void draw() override;

private:
	sf::Font &font;
	std::unique_ptr<GameMap> map;
	MapBuilder mapBuilder;
	TurnManager turnManager;
	GameGui gui;
};