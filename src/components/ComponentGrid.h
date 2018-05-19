#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Component.h"

class ComponentGrid {
public:
	ComponentGrid(sf::Vector2u size);
	void turnPassed();
	std::shared_ptr<Component> getComponentAt(sf::Vector2u pos);
	void setComponentAt(sf::Vector2u pos, std::shared_ptr<Component> component);
	const sf::Vector2u &getGridSize() const;
	void resize(sf::Vector2u size);

protected:
	std::vector<int> getAdjacentComponentIndexes(sf::Vector2u pos);
	int getIndex(const sf::Vector2u &pos);

private:
	sf::Vector2u gridSize;
	std::vector<std::shared_ptr<Component>> components;

	float heatSpreadFraction; // The amount of heat a component will distribute to adjacent components per turn.
};