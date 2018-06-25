#include "JsonHelp.h"

sf::Color JsonHelp::parseColour(nlohmann::json colourJson) {
	return sf::Color(colourJson[0].get<int>(), colourJson[1].get<int>(), colourJson[2].get<int>(), colourJson[3].get<int>());
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
		nlohmann::json frameCoords = frameJson[0];

		sf::Color colour = sf::Color(0, 0, 0, 0);
		try {
			colour = JsonHelp::parseColour(frameJson.at(1)); // Load the frame colour only if one is specified (otherwise uses the default entity colour).
		}
		catch (nlohmann::detail::out_of_range) {}

		frames.push_back({
			frameCoords[0].get<unsigned int>(), // Texture X.
			frameCoords[1].get<unsigned int>(), // Texture Y.
			colour
		});
	}

	//DEBUG_LOG("Loaded animation '" << animationName << "' with " << frames.size() << " frame(s).");
	DEBUG_LOG("Loaded animation with " << frames.size() << " frame(s).");

	return Animation(sf::milliseconds(json["time"].get<int>()), frames);
}