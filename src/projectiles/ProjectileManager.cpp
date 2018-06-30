#include "ProjectileManager.h"

#include "../JsonHelp.h"

ProjectileManager::ProjectileManager() : Manager("projectile", "projectiles") {}

sf::Vector2f ProjectileManager::getSingleProjectileTextureSize() {
	return tileSize;
}

void ProjectileManager::parseJson(nlohmann::json json) {
	tileSize = sf::Vector2f(json["projectile width"], json["projectile height"]);
}

std::pair<IDs::Projectiles, const ProjectileVisual> ProjectileManager::parseJsonManaged(nlohmann::json json) {
	auto id = json["id"].get<IDs::Projectiles>();

	const ProjectileVisual projectile = { id, std::make_shared<Animation>(JsonHelp::loadAnimation(json["animation"])), sf::milliseconds(json["time between moves"].get<int>()) };
	auto pair = std::make_pair(id, projectile);

	return pair;
}