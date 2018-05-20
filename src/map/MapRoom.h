#pragma once

#include "TileLayer.h"

class MapRoom {
public:
	MapRoom(std::string roomName, sf::Vector2u roomPosition, sf::Vector2u roomSize);
	virtual void build(std::unique_ptr<TileLayer> &tiles);

	const std::string name;
	const sf::Vector2u position;
	const sf::Vector2u size;
};