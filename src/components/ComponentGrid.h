#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Component.h"
#include "../Optional.h"

class ComponentGrid {
public:
	ComponentGrid(sf::Vector2u size);
	void turnPassed();
	Optional<Component> &getComponentAt(sf::Vector2u pos);
	const sf::Vector2u &getGridSize() const;
	void resize(sf::Vector2u size);

	unsigned int getCurrentIntegrity(); // The total integrity of every component in this grid.
	unsigned int getMaxIntegrity();

	unsigned int getMaxPowerStorage();

protected:
	std::vector<int> getAdjacentComponentIndexes(sf::Vector2u pos);
	int getIndex(const sf::Vector2u &pos);

private:
	sf::Vector2u gridSize;
	std::vector<Optional<Component>> components;

	float heatSpreadFraction; // The amount of heat a component will distribute to adjacent components per turn.
};