#pragma once

namespace IDs {
	enum Tiles : char {
		NOTHING = 0,
		GROUND = 1,
		WALL = 2,
		DOOR = 3,
		ROCK = 4
	};
	
	enum Components : char {
		BASIC_HEAT_SINK = 0,
		IMPROVED_HEAT_SINK = 1,
		ADVANCED_HEAT_SINK = 2,
	};

	enum ComponentUpgrades : char {};
}