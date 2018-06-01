#include "ComponentManager.h"

#define COMPONENTS_TEXTURE_PATH "assets/components/components.png"

ComponentManager::ComponentManager() : Manager("component", "components") {}

void ComponentManager::parseJson(nlohmann::json json) {
	iconSize = sf::Vector2f(json["icon width"].get<float>(), json["icon height"].get<float>());
}

std::pair<IDs::Components, const ComponentInfo> ComponentManager::parseJsonManaged(nlohmann::json json) {
	std::pair<IDs::Components, const ComponentInfo> componentPair(
		json["id"].get<IDs::Components>(),
		{
			json["id"].get<IDs::Components>(),
			json["name"].get<std::string>(),
			json["description"].get<std::string>(),
			json["textureX"].get<unsigned int>(),
			json["textureY"].get<unsigned int>(),
			json.value<int>("max integrity", 1),
			json.value<int>("heat level dangerous", 0),
			json.value<int>("heat level fatal", 0),
			json.value<int>("passive power", 0),
			json.value<int>("use power", 0),
			json.value<int>("passive heat", 0),
			json.value<int>("use heat", 0),
			json["possible upgrades"].get<std::vector<IDs::ComponentUpgrades>>()
		}
	);

	DEBUG_LOG("Loaded " << managedName << " '" << componentPair.second.name << "' with ID: " << componentPair.first);
	DEBUG_LOG("Possible upgrades: " << json["possible upgrades"]);

	return componentPair;
}

const sf::Vector2f &ComponentManager::getSingleIconTextureSize() const {
	return iconSize;
}