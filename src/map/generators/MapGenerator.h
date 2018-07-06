#pragma once

#include <memory>
#include "../TileLayer.h"
#include "../EntityLayer.h"

class MapGenerator {
public:
	virtual void generateTiles(std::unique_ptr<TileLayer> &tiles) {}
	virtual void generateEntities(std::unique_ptr<EntityLayer> &entities) {}

protected:
	template <typename T>
	void fillTiles(std::unique_ptr<TileLayer> &tiles, std::vector<T> positions, IDs::Tiles tile, sf::Color colour) {
		for (T pos : positions)
			tiles->setTileAt((sf::Vector2u) pos, tile, colour);
	}
};