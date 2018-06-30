#pragma once

namespace IDs {
	enum Tiles : char {
		NOTHING = 0,
		GROUND = 1,
		WALL = 2,
		DOOR = 3,
		ROCK = 4,
		GRASS = 5,
		DIRT = 6,
		TREE = 7
	};

	enum Components : char {
		FISSION_REACTOR = 0,
		HEAT_SINK = 1,
		DEFENSIVE_PLATING = 2,
		RIFLE = 3
	};

	enum ComponentUpgrades : char {};

	enum Projectiles : char {
		BULLET = 0
	};
}