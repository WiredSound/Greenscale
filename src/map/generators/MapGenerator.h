#pragma once

#include <memory>
#include "../TileLayer.h"
#include "../EntityLayer.h"

class MapGenerator {
public:
	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) {}
	virtual void generateEntities(std::unique_ptr<EntityLayer> &entities) {}
};