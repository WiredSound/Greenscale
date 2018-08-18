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

// Note that is is only called if the component is enabled and the power pool has the same or greater power available than the passive power consumption value.
void Component::yourTurnEnabled(PowerPool &pool) {
	pool.decreasePower(getPassivePowerConsumption());
	decreaseHeat(getPassiveHeatDissipation());
}

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

// Again like yourTurnEnabled, this method is only called if enough power is present in the power pool.
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

ModifierFuncType integrityModifier = [](auto &upgrade) { return upgrade.maxIntegrityModifier; };
unsigned int Component::getMaxIntegrity() { return statWithUpgradesApplied<unsigned int>(fetchInfo().maxIntegrity, integrityModifier); }

ModifierFuncType unsafeHeatLevelModifier = [](auto &upgrade) {return upgrade.unsafeHeatLevelModifier; };
unsigned int Component::getDangerousHeatLevel() { return statWithUpgradesApplied<unsigned int>(fetchInfo().dangerousHeatLevel, unsafeHeatLevelModifier); }
unsigned int Component::getFatalHeatLevel() { return statWithUpgradesApplied<unsigned int>(fetchInfo().fatalHeatLevel, unsafeHeatLevelModifier); }

ModifierFuncType powerModifier = [](auto &upgrade) { return upgrade.powerModifier; };
unsigned int Component::getPassivePowerGeneration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().passivePowerGen, powerModifier); }
unsigned int Component::getPassivePowerConsumption() { return statWithUpgradesApplied<unsigned int>(fetchInfo().passivePowerConsume, powerModifier); }
unsigned int Component::getUsePowerGeneration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().usePowerGen, powerModifier); }
unsigned int Component::getUsePowerConsumption() { return statWithUpgradesApplied<unsigned int>(fetchInfo().usePowerConsume, powerModifier); }
unsigned int Component::getPowerStorage() { return statWithUpgradesApplied<unsigned int>(fetchInfo().powerStorage, powerModifier); }

ModifierFuncType heatModifier = [](auto &upgrade) { return upgrade.heatModifier; };
unsigned int Component::getPassiveHeatDissipation() { return statWithUpgradesApplied<unsigned int>(fetchInfo().passiveHeatDissipate, heatModifier); }
unsigned int Component::getPassiveHeatGeneration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().passiveHeatGen, heatModifier); }
unsigned int Component::getUseHeatDissipation() { return statWithUpgradesApplied<unsigned int>(fetchInfo().useHeatDissipate, heatModifier); }
unsigned int Component::getUseHeatGeneration() { return statWithUpgradesApplied<unsigned int>(fetchInfo().useHeatGen, heatModifier); }

ModifierFuncType transportModifier = [](auto &upgrade) { return upgrade.transportModifier; };
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

bool Component::isWeapon() {
	// A 'weapon' is defined as a component that produces some projectiles and has a range of at least 1 tile (at least until melee weapons are added that is).
	return getProjectileCount() > 0 && getProjectileRange() >= 1;
}
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