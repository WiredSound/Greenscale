#pragma once

#include <SFML/System/Vector2.hpp>
#include "EntityInfo.h"
#include "../Manager.h"
#include "../IDs.h"

/**
 * Uses the Manager class template to load entity data from a JSON file.
 */
class EntityManager : public Manager<IDs::Entities, EntityInfo> {
public:
	EntityManager();
	virtual void parseJson(nlohmann::json json) override;
	virtual std::pair<IDs::Entities, const EntityInfo> parseJsonManaged(nlohmann::json json) override;
	sf::Vector2f getFrameSize();

private:
	sf::Vector2f frameSize;
};