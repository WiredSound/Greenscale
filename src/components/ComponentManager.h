#pragma once

#include <SFML/System/Vector2.hpp>
#include "../Manager.h"
#include "../IDs.h"
#include "ComponentInfo.h"

class ComponentManager : public Manager<IDs::Components, ComponentInfo> {
public:
	ComponentManager();
	virtual void parseJson(nlohmann::json json) override;
	virtual std::pair<IDs::Components, const ComponentInfo> parseJsonManaged(nlohmann::json json) override;

	const sf::Vector2f &getSingleIconTextureSize() const;

private:
	sf::Vector2f iconSize;
};