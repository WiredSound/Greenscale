#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Animation.h"
#include "components/Damage.h"

namespace JsonHelp {
	sf::Color parseColour(nlohmann::json colourJson);
	Damage parseDamage(nlohmann::json json);
	Animation loadAnimation(nlohmann::json &json);

	/*
	template <typename Vector, typename Types>
	Vector parseVector(nlohmann::json vectorJson) {
	try {
	return Vector(vectorJson["x"].get<Types>(), vectorJson["y"].get<Types>());
	return Vector(vectorJson[0].get<Types>(), vectorJson[1].get<Types>());
	}
	catch (nlohmann::detail::exception) {
	DEBUG_LOG_ERROR("Failed to parse a json vector!");
	}

	return Vector();
	}
	*/
}