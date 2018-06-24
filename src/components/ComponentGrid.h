#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Component.h"
#include "../Optional.h"

class ComponentGrid {
public:
	ComponentGrid(sf::Vector2u size);
	void turnPassed();
	Optional<Component> &getComponentByIndex(unsigned int index);
	Optional<Component> &getComponentAt(sf::Vector2u pos);
	const sf::Vector2u &getGridSize() const;
	void resize(sf::Vector2u size);

	unsigned int getCurrentIntegrity(); // The total integrity of every component in this grid.
	unsigned int getMaxIntegrity();

	unsigned int getMaxPowerStorage();

	Optional<Component> &getEquippedComponent();
	sf::Vector2u getEquippedComponentGridPosition();
	void equipComponent(sf::Vector2u pos);
	void unequipComponent();
	bool isComponentEquipped();

	void applyDamageToRandomComponent(Damage damage);

protected:
	std::vector<unsigned int> getAdjacentComponentIndexes(sf::Vector2u pos);
	std::vector<unsigned int> getFunctionalComponentIndexes(); // 'Functional' means having an integrity greater than 0 in this case.
	unsigned int getIndex(const sf::Vector2u &pos);

private:
	sf::Vector2u gridSize;
	std::vector<Optional<Component>> components;

	bool componentEquipped = false;
	sf::Vector2u equippedPosition;

	float heatSpreadFraction; // The amount of heat a component will distribute to adjacent components per turn.
};