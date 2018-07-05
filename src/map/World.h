#pragma once

#include <map>
#include "MapBuilder.h"

class World {
public:
	World(GameGui &gui, sf::Vector2f tileSize);

	void update(Input &input);
	void draw(sf::RenderWindow &window);

	TurnManager &getTurnManager();

private:
	std::unique_ptr<GameMap> map;
	MapBuilder builder;
	TurnManager turnManager;
	std::vector<std::shared_ptr<Entity>> playerEntities;
};