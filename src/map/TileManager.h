#pragma once

#include <SFML/System/Vector2.hpp>
#include "../Manager.h"
#include "../IDs.h"
#include "Tile.h"

/**
 * Uses the Manager class template to load tile data from a JSON file.
 */
class TileManager : public Manager<IDs::Tiles, Tile> {
public:
	TileManager();
	virtual void parseJson(nlohmann::json json) override;
	virtual std::pair<IDs::Tiles, const Tile> parseJsonManaged(nlohmann::json json) override;

	const sf::Vector2f &getSingleTileTextureSize();

private:
	sf::Vector2f tileSize;
};