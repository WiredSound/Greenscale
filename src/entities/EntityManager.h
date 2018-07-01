#pragma once

#include <SFML/System/Vector2.hpp>
#include "EntityInfo.h"
#include "../Manager.h"
#include "../IDs.h"

class EntityManager : public Manager<IDs::Entities, EntityInfo> {
public:
	EntityManager();
	virtual void parseJson(nlohmann::json json) override;
	virtual std::pair<IDs::Entities, const EntityInfo> parseJsonManaged(nlohmann::json json) override;
	sf::Vector2f getFrameSize();

private:
	sf::Vector2f frameSize;
};