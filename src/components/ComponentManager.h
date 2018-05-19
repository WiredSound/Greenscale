#pragma once

#include "../Manager.h"
#include "../IDs.h"
#include "ComponentInfo.h"

class ComponentManager : public Manager<IDs::Components, ComponentInfo> {
public:
	ComponentManager();
	virtual std::pair<IDs::Components, const ComponentInfo> parseJson(nlohmann::json json);
};