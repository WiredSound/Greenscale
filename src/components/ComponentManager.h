#pragma once

#include "../Manager.h"
#include "../IDs.h"
#include "ComponentInfo.h"

class ComponentManager : public Manager<IDs::Components, ComponentInfo> {
public:
	ComponentManager();
	virtual void parseJson(nlohmann::json json) {}
	virtual std::pair<IDs::Components, const ComponentInfo> parseJsonManaged(nlohmann::json json);
};