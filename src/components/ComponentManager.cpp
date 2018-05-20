#include "ComponentManager.h"

#define COMPONENTS_TEXTURE_PATH "assets/components/components.png"

ComponentManager::ComponentManager() : Manager("component", "components") {}

std::pair<IDs::Components, const ComponentInfo> ComponentManager::parseJsonManaged(nlohmann::json json) {
	std::pair<IDs::Components, const ComponentInfo> componentPair(
		json["id"].get<IDs::Components>(),
		{
			json["id"].get<IDs::Components>(),
			json["name"].get<std::string>(),
			json["description"].get<std::string>(),
			json["textureX"].get<unsigned int>(),
			json["textureY"].get<unsigned int>(),
			json["max integrity"].get<int>(),
			json["heat level dangerous"].get<int>(),
			json["heat level fatal"].get<int>()
		}
	);

	DEBUG_LOG("Loaded " << managedName << " '" << componentPair.second.name << "' with ID: " << componentPair.first);

	return componentPair;
}