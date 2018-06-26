#include "JsonHelp.h"

sf::Color JsonHelp::parseColour(nlohmann::json colourJson) {
	try {
		return sf::Color(colourJson[0].get<int>(), colourJson[1].get<int>(), colourJson[2].get<int>(), colourJson[3].get<int>());
	}
	catch (nlohmann::json::exception) {
		return sf::Color(0, 0, 0, 0);
	}
}

Damage JsonHelp::parseDamage(nlohmann::json json) {
	return{
		json["kinetic"].get<int>(),
		json["thermal"].get<int>(),
		json["disruption"].get<float>()
	};
}

Animation JsonHelp::loadAnimation(nlohmann::json &json) {
	std::vector<Animation::Frame> frames;

	for (nlohmann::json frameJson : json["frames"]) {
		frames.push_back({
			frameJson[0].get<unsigned int>(), // Texture X.
			frameJson[1].get<unsigned int>(), // Texture Y.
			JsonHelp::parseColour(frameJson[2])
		});
	}

	sf::Time time = sf::milliseconds(json["time"].get<int>());

	DEBUG_LOG("Loaded animation with " << frames.size() << " frame(s) and " << time.asMilliseconds() << "ms between frames.");

	return Animation(time, frames);
}