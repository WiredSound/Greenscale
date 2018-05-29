#pragma once

#include <random>
#include "TileManager.h"
#include "GameMap.h"
#include "SquareRoom.h"
#include "../entities/EntityBuilder.h"
#include "../entities/PlayerController.h"
#include "../components/ComponentBuilder.h"

class MapBuilder {
public:
	MapBuilder(unsigned int seed, sf::RenderWindow &window, GameGui &gui); // The game gui is required by the player controller.
	virtual std::unique_ptr<GameMap> buildMap(sf::Vector2u size, sf::Vector2f tileSize);

protected:
	std::unique_ptr<TileLayer> makeTileLayer(sf::Vector2u size, sf::Vector2f tileSize);
	std::unique_ptr<EntityLayer> makeEntityLayer(sf::Vector2u size, sf::Vector2f tileSize);

private:
	std::shared_ptr<PlayerController> playerController;

	TileManager tileManager;
	EntityBuilder entityBuilder;
	ComponentBuilder componentBuilder;

	std::shared_ptr<sf::Texture> tilesTexture;
	std::shared_ptr<sf::Texture> entitiesTexture;

	std::default_random_engine rand;
};