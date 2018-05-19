#pragma once

#include "../Manager.h"
#include "../IDs.h"
#include "Tile.h"

class TileManager : public Manager<IDs::Tiles, Tile> {
public:
	TileManager();
	virtual std::pair<IDs::Tiles, const Tile> parseJson(nlohmann::json json);
};