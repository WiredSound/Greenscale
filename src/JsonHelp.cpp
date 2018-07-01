#include "JsonHelp.h"

sf::Color JsonHelp::parseColour(const nlohmann::json &colourJson) {
	try {
		return sf::Color(colourJson[0].get<int>(), colourJson[1].get<int>(), colourJson[2].get<int>(), colourJson[3].get<int>());
	}
	catch (nlohmann::json::exception) {
		return sf::Color(0, 0, 0, 0);
	}
}

Damage JsonHelp::parseDamage(const nlohmann::json &json) {
	return{
		json["kinetic"].get<int>(),
		json["thermal"].get<int>(),
		json["disruption"].get<float>()
	};
}

Animation JsonHelp::loadAnimation(const nlohmann::json &json) {
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

std::map<const std::string, std::shared_ptr<Animation>> JsonHelp::loadAnimationsAsMap(const nlohmann::json &json) {
	std::map<const std::string, std::shared_ptr<Animation>> map;

	for (auto it = json.begin(); it != json.end(); it++) {
		std::string key = it.key();
		auto animation = std::make_shared<Animation>(loadAnimation(it.value()));

		DEBUG_LOG("Loaded animation from animation list with key: " << key);

		map[key] = animation;
	}

	return map;
}