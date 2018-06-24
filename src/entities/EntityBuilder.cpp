#include "EntityBuilder.h"

void EntityBuilder::loadAllAnimations(const std::string filename) {
	nlohmann::json json;
	std::ifstream file(filename);

	if (file.is_open()) {
		try {
			file >> json;

			frameSize = sf::Vector2f(json["frame width"].get<float>(), json["frame height"].get<float>());

			auto animationsJson = json["animations"];

			robotIdleAnimation = std::make_shared<Animation>(JsonHelp::loadAnimation(animationsJson["robot idle"]));
			robotMovingAnimation = std::make_shared<Animation>(JsonHelp::loadAnimation(animationsJson["robot moving"]));
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

sf::Vector2f EntityBuilder::getFrameSize() {
	return frameSize;
}

Robot EntityBuilder::buildSimpleRobot(sf::Vector2u position, std::shared_ptr<EntityController> controller, Faction faction) {
	return Robot("Simple Robot (" + faction.shorthandName + ")",
		position,
		sf::Vector2u(3, 3),	// Size of the robot's component grid.
		controller,
		faction,
		robotIdleAnimation,
		robotMovingAnimation);
}