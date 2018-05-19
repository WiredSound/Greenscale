#include "EntityBuilder.h"

void EntityBuilder::loadAllAnimations(const std::string filename) {
	nlohmann::json json;
	std::ifstream file(filename);

	if (file.is_open()) {
		try {
			file >> json;

			robotIdleAnimation = std::make_shared<Animation>(loadAnimation(json, "robot idle"));
			robotMovingAnimation = std::make_shared<Animation>(loadAnimation(json, "robot moving"));
		}
		catch (nlohmann::json::type_error &e) {
			DEBUG_LOG_ERROR("Failed to load load entity animations due to type error: " << e.what() << "\nException ID: " << e.id);
		}
		catch (nlohmann::json::parse_error &e) {
			DEBUG_LOG_ERROR("Failed to load load entity animations due to parse error: " << e.what() << "\nException ID: " << e.id << "\nAt byte: " << e.byte);
		}

		file.close();
	}
}

Robot EntityBuilder::buildSimpleRobot(sf::Vector2u position, std::shared_ptr<EntityController> controller, Faction faction) {
	return Robot("Simple Robot (" + faction.shorthandName + ")",
		position,
		sf::Vector2u(3, 3),	// Size of the robot's component grid.
		controller,
		faction,
		10,					// Robot's integrity.
		robotIdleAnimation,
		robotMovingAnimation);
}

Animation EntityBuilder::loadAnimation(nlohmann::json &animationsJson, const std::string animationName) {
	nlohmann::json json = animationsJson[animationName];

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

	DEBUG_LOG("Loaded animation '" << animationName << "' with " << frames.size() << " frame(s).");

	return Animation(sf::milliseconds(json["time"].get<int>()), frames);
}