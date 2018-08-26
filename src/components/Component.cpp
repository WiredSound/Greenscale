#include "Component.h"

#include "PowerPool.h"
#include "../Random.h"
#include "../entities/Entity.h"
#include "../map/GameMap.h"

Random Component::random = Random();

Component::Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager)
	: id(componentId), manager(componentManager), integrity(getMaxIntegrity()) {
}

const ComponentInfo &Component::fetchInfo() {
	return manager->get(id);
}

/**
 * This method is called once at the end of the owning entity's turn.
 * Should the component be enabled and have sufficent power, Component::yourTurnEnabled is called. If there is not enough power available for this component then it becomes disabled for 1 turn.
 * If the component is at a dangerous heat level then there is a posibility it may become disable for 1 to 3 turns.
 */
void Component::yourTurn(Entity &entity, PowerPool &pool, Console &console) {
	if (disabledForTurns > 0)
		disabledForTurns--;

	if (isEnabled()) {
		pool.increasePower(getPassivePowerGeneration());
		increaseHeat(getPassiveHeatGeneration());

		if (pool.hasSufficientPower(getPassivePowerConsumption())) {
			DEBUG_LOG("Component " << getName() << " has enough power (" << getPassivePowerConsumption() << " of " << pool.getPowerLevel() << ") to call yourTurnEnabled!");
			yourTurnEnabled(pool);
		}
		else if (disabledForTurns == 0) {
			DEBUG_LOG("Component " << getName() << " has been disabled due to a lack of power!");
			disabledForTurns += 1;
		}
	}

	int disabledForHeat = 0;

	if (atFatalHeatLevel() && random.percentageChange(80))
		disabledForHeat = random.integerRange(2, 3);
	else if (heat >= getDangerousHeatLevel() && random.percentageChange(50))
		disabledForHeat = random.integerRange(1, 2);

	if (disabledForHeat > 0) {
		disabledForTurns += disabledForHeat;

		Console::MessageType messageType = entity.isMemberOfPlayerFaction() ? Console::MessageType::WARNING : Console::MessageType::INFO;
		console.display({ entity.getFullName() + " had component " + getName() + " become disabled for " + std::to_string(disabledForHeat) + " more turns due to overheating!", messageType });
	}
}

/**
 * Called by Component::yourTurn if this component is enabled and the power pool has the same or greater power available than the passive power consumption value.
 * Unless overriden, this method consumes power based on the passive power consumption value and dissipates heat based on the passive heat dissipation value.
 */
void Component::yourTurnEnabled(PowerPool &pool) {
	pool.decreasePower(getPassivePowerConsumption());
	decreaseHeat(getPassiveHeatDissipation());
}

/**
 * Called when the owning entity equips and uses this component.
 * \param user The user of this component.
 * \param path The usage path - usually built by Component::buildProjectilePath.
 * \param pool The power available for this component to use or add to.
 * \return Components can optionally return a collection of projectile arcs which are then added to the map (see RangedComponent).
 */
std::vector<ProjectileArc> Component::use(Entity &user, MovementPath path, PowerPool &pool, Console &console) {
	if (isEnabled()) {
		pool.increasePower(getUsePowerGeneration());
		increaseHeat(getUseHeatGeneration());

		if (pool.hasSufficientPower(getUsePowerConsumption())) {
			DEBUG_LOG("Component " << getName() << " has enough power (" << getUsePowerConsumption() << " of " << pool.getPowerLevel() << ") to call useEnabled!");
			return useEnabled(user, path, pool, console);
		}
		else {
			console.display({ user.getFullName() + " was unable to use component " + getName() + " due to a lack of power - only " + std::to_string(pool.getPowerLevel())
				+ " of the required " + std::to_string(getUsePowerConsumption()) + " was available!", (user.isMemberOfPlayerFaction() ? Console::MessageType::WARNING : Console::MessageType::INFO) });
		}
	}

	return std::vector<ProjectileArc>();
}

/**
 * Called by Component::use when the component is enabled and the has access to sufficient power.
 * Unless overriden, this method consumes power based on the active/use power consumption value and dissipates heat based on the active/use heat dissipation value.
 */
std::vector<ProjectileArc> Component::useEnabled(Entity &user, MovementPath path, PowerPool &pool, Console &console) {
	console.display({ user.getFullName() + " used component: " + getName(), (user.isMemberOfPlayerFaction() ? Console::MessageType::INFO : Console::MessageType::WARNING) });

	pool.decreasePower(getUsePowerConsumption());
	decreaseHeat(getUseHeatDissipation());

	return std::vector<ProjectileArc>();
}

// Standard components:
std::string Component::getName() { return fetchInfo().name; }
std::string Component::getDescription() { return fetchInfo().description; }
unsigned int Component::getIntegrity() { return integrity; }
unsigned int Component::getHeatLevel() { return heat; }

std::vector<IDs::ComponentUpgrades> Component::getPossibleUpgrades() { return fetchInfo().possibleUpgrades; }

Component::ModifierFunc integrityModifier = [](auto &upgrade) { return upgrade.maxIntegrityModifier; };
unsigned int Component::getMaxIntegrity() { return statWithUpgradesApplied<unsigned int>(fetchInfo().maxIntegrity, integrityModifier); }

Component::ModifierFunc unsafeHeatLevelModifier = [](auto &upgrade) {return upgrade.unsafeHeatLevelModifier; };
unsigned int Component::getDangerousHeatLevel() { return statWithUpgradesApplied<unsigned int>(fetchInfo().dangerousHeatLevel, unsafeHeatLevelModifier); }
unsigned int Component::getFatalHeatLevel() { return statWithUpgradesApplied<unsigned int>(fetchInfo().fatalHeatLevel, unsafeHeatLevelModifier); }

Component::ModifierFunc powerModifier = [](auto &upgrade) { return upgrade.powerModifier; };
unsigned int Component::getPassivePowerGeneration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().passivePowerGen, powerModifier); }
unsigned int Component::getPassivePowerConsumption() { return statWithUpgradesApplied<unsigned int>(fetchInfo().passivePowerConsume, powerModifier); }
unsigned int Component::getUsePowerGeneration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().usePowerGen, powerModifier); }
unsigned int Component::getUsePowerConsumption() { return statWithUpgradesApplied<unsigned int>(fetchInfo().usePowerConsume, powerModifier); }
unsigned int Component::getPowerStorage() { return statWithUpgradesApplied<unsigned int>(fetchInfo().powerStorage, powerModifier); }

Component::ModifierFunc heatModifier = [](auto &upgrade) { return upgrade.heatModifier; };
unsigned int Component::getPassiveHeatDissipation() { return statWithUpgradesApplied<unsigned int>(fetchInfo().passiveHeatDissipate, heatModifier); }
unsigned int Component::getPassiveHeatGeneration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().passiveHeatGen, heatModifier); }
unsigned int Component::getUseHeatDissipation() { return statWithUpgradesApplied<unsigned int>(fetchInfo().useHeatDissipate, heatModifier); }
unsigned int Component::getUseHeatGeneration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().useHeatGen, heatModifier); }

Component::ModifierFunc transportModifier = [](auto &upgrade) { return upgrade.transportModifier; };
unsigned int Component::getMovementRange() { return statWithUpgradesApplied<unsigned int>(fetchInfo().movementRange, transportModifier); }

// Ranged components:
IDs::Projectiles Component::getProjectileId() { return IDs::Projectiles::BULLET; }
unsigned int Component::getProjectileCount() { return 0; }
Damage Component::getProjectileDamage() { return Damage(); }
unsigned int Component::getProjectileRange() { return 0; }
unsigned int Component::getProjectilePenetration() { return 0; }

// Spawner components:
unsigned int Component::getSpawnerEntityCount() { return 0; }
IDs::Entities Component::getSpawnerEntityId() { return IDs::Entities::TROOP_01; }

sf::Vector2f Component::getIconTextureSize() {
	return manager->getSingleIconTextureSize();
}

int Component::applyDamage(Damage damage) {
	applyKineticDamage(damage.kinetic);
	applyThermalDamage(damage.thermal);
	return applyDisruption(damage.disruption); // The number of turns the component is disabled for after applying disruption is returned when damage is applied.
}

void Component::applyKineticDamage(int kinetic) {
	reduceIntegrity(kinetic);
}
void Component::applyThermalDamage(int heat) {
	increaseHeat(heat);
}
int Component::applyDisruption(float disruption) {
	if (random.percentageChange(disruption)) {
		int disableFor = random.integerRange(1, 2);
		disabledForTurns += disableFor;

		return disableFor;
	}

	return 0;
}

void Component::increaseIntegrity(unsigned int amount) {
	integrity += amount;

	if (integrity > getMaxIntegrity())
		integrity = getMaxIntegrity();
}

void Component::reduceIntegrity(unsigned int amount) {
	if (integrity >= amount)
		integrity -= amount;
	else
		integrity = 0;
}

void Component::increaseHeat(unsigned int amount) {
	heat += amount;
}

void Component::decreaseHeat(unsigned int amount) {
	heat = heat >= amount ? (heat - amount) : 0;
}

/**
 * Whenever a component is used it requires a path for its usage which is constructed by this method. By having a usage path, components that fire projectiles or perform effects on other elements of
 * the map can specify where this behaviour is directed at. By default however, an incomplete path initialised just with the starting position is returned.
 */
MovementPath Component::buildProjectilePath(sf::Vector2u source, sf::Vector2u target, GameMap *map) {
	return MovementPath(source); // A regular component can only be used on itself.
}

void Component::toggleManualEnable() {
	manualEnable = !manualEnable;
}

void Component::setManualEnable(bool value) {
	manualEnable = value;
}

bool Component::isFunctional() {
	return integrity > 0;
}

bool Component::isDestroyed() {
	return integrity <= 0;
}

bool Component::isEnabled() {
	return disabledForTurns <= 0 && manualEnable && !isDestroyed();
}

/**
 * The colour of a component is determinded by the number of upgrades it has with its opacity based on whether it is enabled or not.
 */
sf::Color Component::getColour() {
	sf::Uint8 opacity = isEnabled() ? 255 : 130; // Opacity is based on whether the component is enabled or not.

	switch (upgrades.size()) {
	case 0: return sf::Color(255, 255, 255, opacity);	// WHITE
	case 1: return sf::Color(0, 255, 0, opacity);		// GREEN
	case 2: return sf::Color(0, 0, 255, opacity);		// BLUE
	case 3: return sf::Color(128, 0, 128, opacity);		// PURPLE
	case 4: return sf::Color(255, 165, 0, opacity);		// ORANGE
	default: return sf::Color(255, 0, 0, opacity);		// RED
	}
}

int Component::calculateActiveNetHeat() {
	return static_cast<int>(getUseHeatGeneration()) - static_cast<int>(getUseHeatDissipation());
}
int Component::calculatePassiveNetHeat() {
	return static_cast<int>(getPassiveHeatGeneration()) - static_cast<int>(getPassiveHeatDissipation());
}
int Component::calculateActiveNetPower() {
	return static_cast<int>(getUsePowerGeneration()) - static_cast<int>(getUsePowerConsumption());
}
int Component::calculatePassiveNetPower() {
	return static_cast<int>(getPassivePowerGeneration()) - static_cast<int>(getPassivePowerConsumption());
}
unsigned int Component::calculateMaxPotentialProjectileDamage() {
	return getProjectileCount() * getProjectileDamage().kinetic; // TODO: Take other forms of damage into account.
}

//! A 'weapon' is defined as a component that produces at least 1 projectile and has a range of at least 1 tile (well, until melee weapons are added that is).
bool Component::isWeapon() {
	return getProjectileCount() > 0 && getProjectileRange() >= 1;
}
//! A 'spawner' is defined as a component with a spawner entity count greater than 0.
bool Component::isSpawner() {
	return getSpawnerEntityCount() > 0;
}
bool Component::isActiveCooling() {
	return calculateActiveNetHeat() < 0;
}
bool Component::isPassiveCooling() {
	return calculatePassiveNetHeat() < 0;
}
bool Component::isActiveHeating() {
	return calculateActiveNetHeat() > 0;
}
bool Component::isPassiveHeating() {
	return calculatePassiveNetHeat() > 0;
}
bool Component::isActivePowerGenerator() {
	return calculateActiveNetPower() > 0;
}
bool Component::isPassivePowerGenerator() {
	return calculatePassiveNetPower() > 0;
}
bool Component::atFatalHeatLevel() {
	return heat >= getFatalHeatLevel();
}
bool Component::atDangerousHeatLevel() {
	return heat >= getDangerousHeatLevel() && heat < getFatalHeatLevel();
}
bool Component::atDangerousOrAboveHeatLevel() {
	return heat >= getDangerousHeatLevel();
}