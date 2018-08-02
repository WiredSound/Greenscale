#pragma once

namespace IDs {
	enum Tiles : unsigned char {
		NOTHING = 0,
		GROUND = 1,
		WALL = 2,
		DOOR = 3,
		ROCK = 4,
		GRASS = 5,
		DIRT = 6,
		BUSH = 7,
		MACHINERY_CONNECTION = 8,
		MACHINERY_NODE = 9,
		MACHINERY_TERMINAL = 10
	};

	enum Components : unsigned char {
		FISSION_REACTOR = 0,
		HEAT_SINK = 1,
		DEFENSIVE_PLATING = 2,
		RIFLE = 3,
		MECHANICAL_LEG = 4
	};

	enum ComponentUpgrades : unsigned char {};

	enum Projectiles : unsigned char {
		BULLET = 0
	};

	enum Entities : unsigned char {
		TROOP_01 = 0,
		RESTRUCTOR_01 = 1,
		SCANNER_01 = 2,
		TROOP_ULTRA = 3
	};
}