#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "ComponentManager.h"
#include "Damage.h"
#include "../map/pathfinding/MovementPath.h"
#include "../Optional.h"
#include "../projectiles/ProjectileArc.h"
#include "../Console.h"
#include "../Random.h"
class Entity;
class GameMap;
class PowerPool;

/*
 * Components allow entities to perform actions such as generate power, shoot projectiles, etc. They are arranged inside a ComponentGrid which, based on how they are positioned, dictates
 * the spread of heat and disruption between components. Components can have a collection of ComponentUpgrade structs which modify the base states of the component. The base stats of a
 * component are defined by its ID which corresponds to a loaded ComponentInfo struct in the ComponentManager.
 */

class Component {
public:
	Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager);
	void yourTurn(Entity &entity, PowerPool &pool, Console &console);
	std::vector<ProjectileArc> use(Entity &user, MovementPath path, PowerPool &pool, Console &console); // Can optionally fire some projectiles (or alternatively just apply changes to self).

	const ComponentInfo &fetchInfo();
	std::string getName();
	std::string getDescription();
	unsigned int getIntegrity();
	unsigned int getHeatLevel();
	unsigned int getMaxIntegrity();
	unsigned int getDangerousHeatLevel();
	unsigned int getFatalHeatLevel();
	unsigned int getPassivePowerGeneration();
	unsigned int getPassivePowerConsumption();
	unsigned int getUsePowerGeneration();
	unsigned int getUsePowerConsumption();
	unsigned int getPassiveHeatDissipation();
	unsigned int getPassiveHeatGeneration();
	unsigned int getUseHeatDissipation();
	unsigned int getUseHeatGeneration();
	unsigned int getPowerStorage();
	unsigned int getMovementRange();
	std::vector<IDs::ComponentUpgrades> getPossibleUpgrades();

	virtual IDs::Projectiles getProjectileId();
	virtual unsigned int getProjectileCount();
	virtual Damage getProjectileDamage();
	virtual unsigned int getProjectileRange();
	virtual unsigned int getProjectilePenetration();

	virtual unsigned int getSpawnerEntityCount();
	virtual IDs::Entities getSpawnerEntityId();

	sf::Vector2f getIconTextureSize();

	int applyDamage(Damage damage);
	void applyKineticDamage(int kinetic);
	void applyThermalDamage(int heat);
	int applyDisruption(float disruption);

	void increaseHeat(unsigned int amount);
	void decreaseHeat(unsigned int amount);

	bool isFunctional();
	bool isDestroyed();
	bool isEnabled();

	virtual MovementPath buildProjectilePath(sf::Vector2u source, sf::Vector2u target, GameMap *map);

	void toggleManualEnable();
	void setManualEnable(bool value);

	sf::Color getColour();

	int calculateActiveNetHeat();
	int calculatePassiveNetHeat();
	int calculateActiveNetPower();
	int calculatePassiveNetPower();
	unsigned int calculateMaxPotentialProjectileDamage();

	bool isWeapon();
	bool isSpawner();
	bool isActiveCooling();
	bool isPassiveCooling();
	bool isActiveHeating();
	bool isPassiveHeating();
	bool isActivePowerGenerator();
	bool isPassivePowerGenerator();

	bool atFatalHeatLevel();
	bool atDangerousHeatLevel();
	bool atDangerousOrAboveHeatLevel();

protected:
	virtual void yourTurnEnabled(PowerPool &pool);
	virtual std::vector<ProjectileArc> useEnabled(Entity &user, MovementPath path, PowerPool &pool, Console &console);

	void increaseIntegrity(unsigned int amount);
	void reduceIntegrity(unsigned int amount);

	std::vector<ComponentUpgrade> upgrades;

	static Random random;

private:
	IDs::Components id;
	std::shared_ptr<ComponentManager> manager;

	bool manualEnable;

	unsigned int integrity;
	unsigned int heat = 0;
	unsigned int disabledForTurns = 0;

protected:
	using ModifierFunc = std::function<float(const ComponentUpgrade&)>;

	// This template is a replacement for the very ugly macro that was employed previously.
	// It takes a base stat (eg. the components max integrity) and then goes through all the upgrades the component has and applies them.
	// The modifierFunc argument takes each component upgrade and returns the modifier that should be used (eg. upgrade.maxIntegrityModifier).
	template <typename T>
	T statWithUpgradesApplied(T baseValue, ModifierFunc modiferFunc) {
		T value = baseValue;

		for (const ComponentUpgrade &upgrade : upgrades) {
			auto increase = modiferFunc(upgrade);
			value += static_cast<T>(increase);
		}

		return value;
	}
};