#pragma once

/**
 * Components, component upgrades, projectiles, tile and entities are all referenced via an ID system.
 * The IDs namespace stores all the enums that represent these different items.
 */
namespace IDs {
	//! Tile IDs.
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

	//! Component IDs.
	enum Components : unsigned char {
		FISSION_REACTOR = 0,
		HEAT_SINK = 1,
		DEFENSIVE_PLATING = 2,
		RIFLE = 3,
		MECHANICAL_LEG = 4,
		TROOP_FABRICATOR = 5
	};

	//! Component upgrade IDs.
	enum ComponentUpgrades : unsigned char {};

	//! Projectile IDs.
	enum Projectiles : unsigned char {
		BULLET = 0
	};

	//! Entity IDs.
	enum Entities : unsigned char {
		TROOP_01 = 0,
		RESTRUCTOR_01 = 1,
		SCANNER_01 = 2,
		TROOP_ULTRA = 3
	};
}