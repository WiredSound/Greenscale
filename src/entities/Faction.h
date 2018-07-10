#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

// TODO: Add proper factions (Church of Tsuki, Atorus, etc) with full descriptions and their opinions of other factions (which the player can influence).
// TODO: Instead of turn order being decided upon an entity's faction, it should instead be determined by the entity's turn priority value which can be modified by installing different components.

class Faction {
public:
	static const Faction UNALIGNED;
	static const Faction PLAYER;
	static const Faction ROGUE;
	static const Faction CORPORATION;

	const std::string name;
	const std::string shorthandName;
	const sf::Color colour;
	const char priority; // Lower priority will be give its turn first.

	bool operator==(const Faction &other);

private:
	Faction(std::string FactionName, std::string factionShorthandName, sf::Color factionColour, char factionPriority);
};