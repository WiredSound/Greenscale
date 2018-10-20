#pragma once

#include "Component.h"

class SpawnerComponent : public Component {
public:
	using Component::Component;

	IDs::Entities getSpawnerEntityId() override;
	unsigned int getSpawnerEntityCount() override;

protected:
	std::vector<ProjectileArc> useEnabled(Entity &user, MovementPath path, PowerPool &pool, Console &console) override;
};