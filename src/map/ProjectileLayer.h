#pragma once

#include <vector>
#include "MapLayer.h"
#include "../projectiles/ProjectileArc.h"

class ProjectileLayer : public MapLayer {
public:
	using MapLayer::MapLayer;
	void update(GameMap *map);

	bool areAllArcsComplete() const;
	void fireArcs(std::vector<ProjectileArc> addArcs);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<ProjectileArc> arcs;
};
