#pragma once

#include <memory>
#include "../TileLayer.h"
#include "../GameMap.h"
#include "../../Random.h"
#include "../../entities/EntityBuilder.h"
#include "../../components/ComponentBuilder.h"

class MapGenerator {
public:
	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) {}
	virtual void generateEntities(std::unique_ptr<GameMap> &map, EntityBuilder &entityBuilder, ComponentBuilder &componentBuilder) {}

protected:
	Random random;
};