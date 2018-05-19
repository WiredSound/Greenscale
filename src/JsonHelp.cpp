#include "JsonHelp.h"

sf::Color JsonHelp::parseColour(nlohmann::json colourJson) {
	return sf::Color(colourJson[0].get<int>(), colourJson[1].get<int>(), colourJson[2].get<int>(), colourJson[3].get<int>());
}