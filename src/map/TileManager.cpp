#include "map/TileManager.h"

#include "JsonHelp.h"

TileManager::TileManager() : Manager("tile", "tiles") {}

void TileManager::parseJson(nlohmann::json json) {
	tileSize = sf::Vector2f(json["tile width"].get<float>(), json["tile height"].get<float>());
}

std::pair<IDs::Tiles, const Tile> TileManager::parseJsonManaged(nlohmann::json json) {
	auto id = json["id"].get<IDs::Tiles>();

	std::pair<IDs::Tiles, const Tile> tilePair(
		id,
		{
			id,
			json["name"],
			json["textureX"].get<unsigned int>(),
			json["textureY"].get<unsigned int>(),
			JsonHelp::parseColour(json["colour"]),
			json["blocking"].get<bool>(),
			json["cover"].get<float>(),
			json["strength"].get<unsigned int>(),
			json.value<IDs::Tiles>("replacement on destruction", id)
		}
	);

	return tilePair;
}

const sf::Vector2f &TileManager::getSingleTileTextureSize() {
	return tileSize;
}
