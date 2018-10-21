#include "entities/EntityManager.h"

#include "JsonHelp.h"

EntityManager::EntityManager() : Manager("entity", "entities") {}

void EntityManager::parseJson(nlohmann::json json) {
	frameSize = sf::Vector2f(json["frame width"].get<float>(), json["frame height"].get<float>());
}

std::pair<IDs::Entities, const EntityInfo> EntityManager::parseJsonManaged(nlohmann::json json) {
	DEBUG_LOG("Loading " << managedName << " " << json["name"] << " of type " << json["type"] << "...");

	auto id = json["id"].get<IDs::Entities>();
	const EntityInfo info = {
		id,
		json["name"].get<std::string>(),
		json["description"].get<std::string>(),
		json["type"].get<std::string>(),
		json.find("size") != json.end() ? sf::Vector2u(json["size"][0], json["size"][1]) : sf::Vector2u(1, 1),
		JsonHelp::loadAnimationsAsMap(json["animations"])
	};

	return std::make_pair(id, info);
}

sf::Vector2f EntityManager::getFrameSize() {
	return frameSize;
}
