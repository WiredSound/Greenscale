#pragma once

#include <map>
#include "MapBuilder.h"
#include "../TurnManager.h"

class World {
public:
	World(GameGui &gui, Camera &camera, sf::Vector2f tileSize);

	void update(Input &input);
	void draw(sf::RenderWindow &window);

	TurnManager &getTurnManager();

private:
	std::unique_ptr<GameMap> map;
	MapBuilder builder;
	TurnManager turnManager;
	std::vector<std::shared_ptr<Entity>> playerEntities;

	std::shared_ptr<Entity> constructNewPlayer(IDs::Entities id, sf::Vector2u position, Faction faction);
};