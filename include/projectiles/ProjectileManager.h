#pragma once

#include <SFML/System/Vector2.hpp>
#include "../Manager.h"
#include "../IDs.h"
#include "Projectile.h"

class ProjectileManager : public Manager<IDs::Projectiles, ProjectileVisual> {
public:
	ProjectileManager();

	sf::Vector2f getSingleProjectileTextureSize();

protected:
	virtual void parseJson(nlohmann::json json) override;
	virtual std::pair<IDs::Projectiles, const ProjectileVisual> parseJsonManaged(nlohmann::json json) override;

private:
	sf::Vector2f tileSize;
};