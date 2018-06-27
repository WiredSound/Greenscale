#pragma once

#include <random>
#include <SFML/Graphics/Texture.hpp>
#include "ComponentManager.h"
#include "../map/pathfinding/MovementPath.h"
#include "../Optional.h"
#include "../projectiles/ProjectileArc.h"
#include "Damage.h"
class Entity;
class GameMap;

class Component {
public:
	Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager);
	void yourTurn();
	bool use();

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

	virtual std::vector<ProjectileArc> use(MovementPath path); // Can optionally fire some projectiles (or alternatively just apply changes to self).
	virtual MovementPath buildProjectilePath(sf::Vector2u source, sf::Vector2u target, GameMap *map);

	void toggleManualEnable();

	sf::Color getColour();

protected:
	virtual void yourTurnEnabled();
	virtual bool useEnabled();

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

	std::default_random_engine rand;
	std::uniform_int_distribution<int> randomTurnsMissed;
	std::uniform_int_distribution<int> randomPercentage;
};