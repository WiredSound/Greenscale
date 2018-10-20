#pragma once

#include <map>
#include "MapBuilder.h"
#include "../TurnManager.h"

/**
 * The World class is tasked with creating and managing connected maps that together make up the overworld. It calls upon the TurnManager to allow for the turn system to work and uses the MapBuilder
 * to construct new maps. It also keeps a list of player controlled/required entities so that these entities can be moved between maps.
 */
class World {
public:
	World(Camera &camera, std::shared_ptr<PlayerController> controller, Console &consoleRef, sf::Vector2f tileSize);

	void update(Input &input);
	void draw(sf::RenderWindow &window);

	TurnManager &getTurnManager();

private:
	std::unique_ptr<GameMap> map;
	Console &console;
	MapBuilder builder;
	TurnManager turnManager;
	std::vector<std::shared_ptr<Entity>> playerEntities;

	std::shared_ptr<Entity> constructNewPlayer(IDs::Entities id, sf::Vector2u position, Faction faction);
};