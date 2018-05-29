#pragma once

namespace IDs {
	enum Tiles : char {
		NOTHING = 0,
		GROUND = 1,
		WALL = 2,
		DOOR = 3,
		ROCK = 4,
		GRASS = 5,
		DIRT = 6
	};

	enum Components : char {
		HEAT_SINK = 0,
		DEFENSIVE_PLATING = 1
	};

	enum ComponentUpgrades : char {};
}