#pragma once

#include "MapRoom.h"
#include "../IDs.h"

class SquareRoom : public MapRoom {
public:
	SquareRoom(std::string roomName, sf::Vector2u roomPosition, sf::Vector2u roomSize, IDs::Tiles flooring, IDs::Tiles walls);
	virtual void build(std::unique_ptr<TileLayer> &tiles) override;

	const IDs::Tiles flooringTile, wallTile;
};