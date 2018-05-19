#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>

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