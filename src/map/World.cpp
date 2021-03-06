#include "map/World.h"

#include "map/generators/PlainsGenerator.h"
#include "map/generators/TransmissionTowerFloorGenerator.h"
#include "entities/controllers/FollowEntityController.h"
#include "entities/controllers/SearchAndDestroyController.h"
#include "Camera.h"

World::World(Camera &camera, std::shared_ptr<PlayerController> controller, Console &consoleRef, sf::Vector2f tileSize)
	: builder(tileSize, { Faction::PLAYER, Faction::ROGUE }, controller, consoleRef), turnManager(camera), console(consoleRef)
{
	auto player = constructNewPlayer(IDs::Entities::TROOP_01, sf::Vector2u(1, 1), Faction::PLAYER);

	auto follower = builder.entityBuilder.buildEntity(IDs::Entities::SCANNER_01, "Follower", sf::Vector2u(1, 3), Faction::ROGUE, sf::Vector2u(2, 2), std::make_shared<FollowEntityController>(player, 2, console));
	follower->getComponentGrid().getComponentAt(sf::Vector2u(0, 0)).set(builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::FISSION_REACTOR));
	follower->getComponentGrid().getComponentAt(sf::Vector2u(0, 1)).set(builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::MECHANICAL_LEG));
	follower->getComponentGrid().getComponentAt(sf::Vector2u(0, 1))->setManualEnable(true);

	playerEntities.push_back(player);
	playerEntities.push_back(follower);

	map = builder.buildMap(sf::Vector2u(75, 75), playerEntities,
	{ std::shared_ptr<MapGenerator>(new PlainsGenerator(IDs::Tiles::GRASS, sf::Color(130, 200, 80), sf::Color(130, 255, 80), { IDs::Tiles::BUSH }, 5)),
	  std::make_shared<TransmissionTowerFloorGenerator>(35, 2, IDs::Tiles::WALL, sf::Color(150, 150, 150, 255), IDs::Tiles::GROUND, sf::Color(100, 100, 100, 255)) });
}

/**
 * Calls the required update methods GameMap::update (of the currently loaded map) and TurnManager::update.
 */
void World::update(Input &input) {
	map->update();
	turnManager.update(input, map);

	if (input.isKeyJustPressed(sf::Keyboard::Key::S))
		map->save("M:/Visual Studio Projects/Greenscale/test");
	if (input.isKeyJustPressed(sf::Keyboard::Key::L))
		map->load("M:/Visual Studio Projects/Greenscale/test");
}

/**
 * Calls GameMap::draw for the currently loaded map.
 */
void World::draw(sf::RenderWindow &window) {
	map->draw(window);
}

TurnManager &World::getTurnManager() {
	return turnManager;
}

std::shared_ptr<Entity> World::constructNewPlayer(IDs::Entities id, sf::Vector2u position, Faction faction) {
	auto player = builder.entityBuilder.buildEntity(id, "Player", position, faction, sf::Vector2u(3, 3), builder.playerController);
	auto &grid = player->getComponentGrid();

	grid.getComponentAt(sf::Vector2u(0, 0)) = builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::FISSION_REACTOR);
	grid.getComponentAt(sf::Vector2u(2, 0)) = builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::RIFLE);
	grid.getComponentAt(sf::Vector2u(0, 1)) = builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::MECHANICAL_LEG);
	grid.getComponentAt(sf::Vector2u(1, 2)) = builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::MECHANICAL_LEG);
	grid.getComponentAt(sf::Vector2u(2, 1)) = builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::TROOP_FABRICATOR);
	grid.getComponentAt(sf::Vector2u(1, 0)) = builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::HEAT_SINK);
	grid.getComponentAt(sf::Vector2u(1, 1)) = builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::HEAT_SINK);

	return player;
}
