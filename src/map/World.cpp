#include "World.h"

#include <ctime>
#include "generators/PlainsGenerator.h"
#include "generators/TransmissionTowerFloorGenerator.h"
#include "../Camera.h"

World::World(GameGui &gui, Camera &camera, sf::Vector2f tileSize) : builder(static_cast<unsigned int>(time(0)), gui, tileSize), turnManager(camera) {
	playerEntities.push_back(constructNewPlayer());

	map = builder.buildMap(sf::Vector2u(64, 64), playerEntities,
	{ std::shared_ptr<MapGenerator>(new PlainsGenerator(IDs::Tiles::GRASS, sf::Color(130, 200, 80), sf::Color(130, 255, 80), { IDs::Tiles::BUSH }, 5)),
	  std::make_shared<TransmissionTowerFloorGenerator>(25, 2, IDs::Tiles::WALL, sf::Color(150, 150, 150, 255), IDs::Tiles::GROUND, sf::Color(100, 100, 100, 255)) });
}

void World::update(Input &input) {
	map->update();
	turnManager.update(input, map);

	if (input.isKeyJustPressed(sf::Keyboard::Key::S))
		map->save("M:/Visual Studio Projects/Greenscale/test");
	if (input.isKeyJustPressed(sf::Keyboard::Key::L))
		map->load("M:/Visual Studio Projects/Greenscale/test");
}

void World::draw(sf::RenderWindow &window) {
	map->draw(window);
}

TurnManager &World::getTurnManager() {
	return turnManager;
}

std::shared_ptr<Entity> World::constructNewPlayer() {
	auto player = builder.entityBuilder.buildEntity(IDs::Entities::TROOP_01, "Player", sf::Vector2u(1, 1), Faction::PLAYER, builder.playerController);

	player->getComponentGrid().getComponentAt(sf::Vector2u(0, 0)) = builder.componentBuilder.buildComponentNoUpgrades(IDs::Components::FISSION_REACTOR);

	return player;
}