#include "MapRoom.h"

#include "../IDs.h"

MapRoom::MapRoom(std::string roomName, sf::Vector2u roomPosition, sf::Vector2u roomSize) : name(roomName), position(roomPosition), size(roomSize) {}

void MapRoom::build(std::unique_ptr<TileLayer> &tiles) {
	// Default build just fills the room with ground tiles.
	// This should be overridden.

	for (unsigned int x = 0; x < position.x + size.x; x++) {
		for (unsigned int y = 0; y < position.y + size.y; y++) {
			tiles->setTileAt(sf::Vector2u(x, y), IDs::Tiles::GROUND);
		}
	}
}