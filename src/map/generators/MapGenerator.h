#pragma once

#include <memory>
#include "../TileLayer.h"
#include "../GameMap.h"
#include "../../entities/EntityBuilder.h"
#include "../../Random.h"

class MapGenerator {
public:
	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) {}
	virtual void generateEntities(std::unique_ptr<GameMap> &map, EntityBuilder &builder) {}

protected:
	Random random;
};