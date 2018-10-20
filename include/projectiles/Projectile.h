#pragma once

#include "../IDs.h"
#include "../Animation.h"

struct ProjectileVisual {
	IDs::Projectiles id;
	std::shared_ptr<Animation> animation;
	sf::Time timeBetweenMoves;
};