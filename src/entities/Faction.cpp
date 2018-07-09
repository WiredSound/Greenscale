#include "Faction.h"

#define FACTIONS_OPACITY 230

Faction::Faction(std::string FactionName, std::string factionShorthandName, sf::Color factionColour, char factionPriority)
	: name(FactionName), shorthandName(factionShorthandName), colour(factionColour), priority(factionPriority) {}

bool Faction::operator==(const Faction &other) {
	return name == other.name;
}

const Faction Faction::UNALIGNED(
	"Unaligned",
	"UNALIGNED",
	sf::Color(255, 255, 255, FACTIONS_OPACITY),
	0
);

/*
The faction of robots controlled by the player.
*/
const Faction Faction::PLAYER(
	"Player Controlled",
	"PLAYER",
	sf::Color(0, 250, 154, FACTIONS_OPACITY),
	1 // Player entities can act first.
);

/*
The collection of robots that have rebelled against the corporation. They tend to act
neutral or as an ally of player aligned robots.
*/
const Faction Faction::ROGUE(
	"Rogue",
	"ROGUE",
	sf::Color(100, 100, 255, FACTIONS_OPACITY),
	2 // Rogue entities act after player entities.
);

/*
Robots controlled by the corporation. Most will flee the player except for robots
designed to engage in battle which will attack player aligned robots.
*/
const Faction Faction::CORPORATION(
	"Corporation",
	"CORP",
	sf::Color(255, 50, 50, FACTIONS_OPACITY),
	3 // Corporation entities are given their turn last.
);