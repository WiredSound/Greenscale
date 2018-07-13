#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "ComponentManager.h"
#include "Damage.h"
#include "../map/pathfinding/MovementPath.h"
#include "../Optional.h"
#include "../projectiles/ProjectileArc.h"
#include "../Console.h"
class Entity;
class GameMap;

/*
 * Components allow entities to perform actions such as generate power, shoot projectiles, etc. They are arranged inside a ComponentGrid which, based on how they are positioned, dictates
 * the spread of heat and disruption between components. Components can have a collection of ComponentUpgrade structs which modify the base states of the component. The base stats of a
 * component are defined by its ID which corresponds to a loaded ComponentInfo struct in the ComponentManager.
 */

class Component {
public:
	Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager);
	void yourTurn();
	std::vector<ProjectileArc> use(Entity &user, MovementPath path, Console &console); // Can optionally fire some projectiles (or alternatively just apply changes to self).

	const ComponentInfo &fetchInfo();
	std::string getName();
	std::string getDescription();
	int getIntegrity();
	int getMaxIntegrity();
	int getHeatLevel();
	int getDangerousHeatLevel();
	int getFatalHeatLevel();
	int getPassivePower();
	int getUsePower();
	int getPassiveHeat();
	int getUseHeat();
	int getPowerStorage();
	std::vector<IDs::ComponentUpgrades> getPossibleUpgrades();

	sf::Vector2f getIconTextureSize();

	void applyDamage(Damage damage);
	void applyKineticDamage(int kinetic);
	void applyThermalDamage(int heat);
	void applyDisruption(float disruption);

	void increaseHeat(int amount);
	//void increasePower(int amount);

	bool isDestroyed();
	bool isEnabled();

	virtual MovementPath buildProjectilePath(sf::Vector2u source, sf::Vector2u target, GameMap *map);

	void toggleManualEnable();

	sf::Color getColour();

protected:
	virtual void yourTurnEnabled();
	virtual std::vector<ProjectileArc> useEnabled(Entity &user, MovementPath path, Console &console);

	void increaseIntegrity(int amount);
	void reduceIntegrity(int amount);

	std::vector<ComponentUpgrade> upgrades;

private:
	IDs::Components id;
	std::shared_ptr<ComponentManager> manager;

	bool manualEnable;

	int integrity;
	int heat = 0;
	int disabledForTurns = 0;
};