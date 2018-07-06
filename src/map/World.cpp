#include "World.h"

#include <ctime>
#include "generators/PlainsGenerator.h"
#include "generators/TransmissionTowerFloorGenerator.h"

World::World(GameGui &gui, sf::Vector2f tileSize) : builder(static_cast<unsigned int>(time(0)), gui, tileSize) {
	playerEntities.push_back(builder.entityBuilder.buildEntity(IDs::Entities::TROOP_01, "Player", sf::Vector2u(1, 1), Faction::PLAYER, builder.playerController));

	map = builder.buildMap(sf::Vector2u(64, 64), playerEntities,
	{ std::shared_ptr<MapGenerator>(new PlainsGenerator(IDs::Tiles::GRASS, sf::Color(130, 200, 80), sf::Color(130, 255, 80), { IDs::Tiles::BUSH }, 5)),
	  std::make_shared<TransmissionTowerFloorGenerator>(30, IDs::Tiles::WALL, sf::Color(150, 150, 150, 255), IDs::Tiles::GROUND, sf::Color(100, 100, 100, 255)) });
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