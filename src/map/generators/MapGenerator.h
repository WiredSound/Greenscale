#pragma once

#include <memory>
#include "../TileLayer.h"
#include "../GameMap.h"
#include "../../Random.h"
#include "../../entities/EntityBuilder.h"
#include "../../components/ComponentBuilder.h"

/**
 * Used by MapBuilder for the procedual generation of tiles and entities.
 * When building a map using MapBuilder::buildMap the caller can specify multiple MapGenerator instances which are tasked with the actual generation.
 */
class MapGenerator {
public:
	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) {}
	virtual void generateEntities(std::unique_ptr<GameMap> &map, EntityBuilder &entityBuilder, ComponentBuilder &componentBuilder) {}

protected:
	Random random;
};