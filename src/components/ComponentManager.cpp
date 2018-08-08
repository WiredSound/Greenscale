#include "ComponentManager.h"

#include "../JsonHelp.h"

#define COMPONENTS_TEXTURE_PATH "assets/components/components.png"

ComponentManager::ComponentManager() : Manager("component", "components") {}

void ComponentManager::parseJson(nlohmann::json json) {
	iconSize = sf::Vector2f(json["icon width"].get<float>(), json["icon height"].get<float>());
}

std::pair<IDs::Components, const ComponentInfo> ComponentManager::parseJsonManaged(nlohmann::json json) {
	DEBUG_LOG("Loading " << managedName << " " << json["name"] << "...");

	std::pair<IDs::Components, const ComponentInfo> componentPair(
		json["id"].get<IDs::Components>(),
		{
			json["id"].get<IDs::Components>(),
			json["name"].get<std::string>(),
			json["description"].get<std::string>(),
			json.value<std::string>("type", ""),
			json["textureX"].get<unsigned int>(),
			json["textureY"].get<unsigned int>(),
			json.value<unsigned int>("max integrity", 1),
			json.value<unsigned int>("heat level dangerous", 0),
			json.value<unsigned int>("heat level fatal", 0),
			json.value<unsigned int>("passive power generation", 0),
			json.value<unsigned int>("passive power consumption", 0),
			json.value<unsigned int>("use power generation", 0),
			json.value<unsigned int>("use power consumption", 0),
			json.value<unsigned int>("passive heat dissipation", 0),
			json.value<unsigned int>("passive heat generation", 0),
			json.value<unsigned int>("use heat dissipation", 0),
			json.value<unsigned int>("use heat generation", 0),
			json.value<unsigned int>("power storage", 0),
			json.value<unsigned int>("movement range", 0),
			json.value<std::vector<IDs::ComponentUpgrades>>("possible upgrades", {}),
			json.value<IDs::Projectiles>("projectile id", IDs::Projectiles::BULLET),
			json.value<unsigned int>("projectile count", 1),
			json.find("projectile damage") != json.end() ? JsonHelp::parseDamage(json["projectile damage"]) : Damage(),
			json.value<unsigned int>("projectile range", 1),
			json.value<unsigned int>("projectile penetration", 0),
			json.value<IDs::Entities>("spawn entity id", IDs::Entities::TROOP_01)
		}
	);

	DEBUG_LOG("Possible upgrades: " << json["possible upgrades"]);

	return componentPair;
}

const sf::Vector2f &ComponentManager::getSingleIconTextureSize() const {
	return iconSize;
}