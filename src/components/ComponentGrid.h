#pragma once

#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Component.h"
#include "PowerPool.h"
#include "../Optional.h"

class ComponentGrid {
public:
	ComponentGrid(sf::Vector2u size);
	void turnPassed(Entity &entity, Console &console);
	Optional<Component> &getComponentByIndex(unsigned int index);
	Optional<Component> &getComponentAt(sf::Vector2u pos);
	Optional<Component> &getRandomComponent();
	const sf::Vector2u &getGridSize() const;
	void resize(sf::Vector2u size);

	unsigned int getCurrentIntegrity(); // The total integrity of every component in this grid.
	unsigned int getMaxIntegrity();

	unsigned int getPowerStored();
	unsigned int getMaxPowerStorage();

	unsigned int getMovementRange();

	Optional<Component> &getEquippedComponent();
	sf::Vector2u getEquippedComponentGridPosition();
	void equipComponent(sf::Vector2u pos);
	void unequipComponent();
	bool isComponentEquipped();

	void swapPositions(sf::Vector2u firstPos, sf::Vector2u secondPos);

	std::vector<ProjectileArc> use(Optional<Component> &component, Entity &user, MovementPath path, Console &console);
	std::vector<ProjectileArc> use(sf::Vector2u position, Entity &user, MovementPath path, Console &console);

	std::vector<sf::Vector2u> findFunctionalPositions();
	std::vector<sf::Vector2u> findWeaponPositions();
	std::vector<sf::Vector2u> findActiveCoolingPositions();
	std::vector<sf::Vector2u> findPassiveCoolingPositions();
	std::vector<sf::Vector2u> findFatalHeatPositions();
	std::vector<sf::Vector2u> findDangerousHeatPositions();
	std::vector<sf::Vector2u> findHotPositions();

protected:
	std::vector<unsigned int> getAdjacentComponentIndexes(sf::Vector2u pos);
	unsigned int getIndex(const sf::Vector2u &pos);

private:
	std::vector<Optional<Component>> components;
	sf::Vector2u gridSize;
	PowerPool power;

	Optional<Component> noComponent;

	bool componentEquipped = false;
	sf::Vector2u equippedPosition;

	float heatSpreadFraction; // The amount of heat a component will distribute to adjacent components per turn.
};