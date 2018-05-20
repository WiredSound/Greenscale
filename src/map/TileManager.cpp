#include "TileManager.h"

#include "../JsonHelp.h"

TileManager::TileManager() : Manager("tile", "tiles") {}

void TileManager::parseJson(nlohmann::json json) {
	tileSize = sf::Vector2f(json["tile width"].get<float>(), json["tile height"].get<float>());
}

std::pair<IDs::Tiles, const Tile> TileManager::parseJsonManaged(nlohmann::json json) {
	std::pair<IDs::Tiles, const Tile> tilePair(
		json["id"].get<IDs::Tiles>(),
		{
			json["id"].get<IDs::Tiles>(),
			json["name"],
			json["textureX"].get<unsigned int>(),
			json["textureY"].get<unsigned int>(),
			JsonHelp::parseColour(json["colour"]),
			json["blocking"].get<bool>(),
			json["cover"].get<float>(),
			json["strength"].get<int>()
		}
	);

	DEBUG_LOG("Loaded " << managedName << " '" << tilePair.second.name << "' with ID: " << tilePair.first);

	return tilePair;
}

const sf::Vector2f &TileManager::getSingleTileTextureSize() {
	return tileSize;
}