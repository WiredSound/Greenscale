#include "Component.h"

#include "../Random.h"
#include "../entities/Entity.h"
#include "../map/GameMap.h"

// This magical little macro takes a value from the ComponentInfo struct of valueName and then applies all the modifiers of modifierName in this component's upgrades:
#define RETURN_VALUE_WITH_UPGRADES(valueName, modifierName) auto baseValue = fetchInfo().valueName; auto value = baseValue; \
															for (const ComponentUpgrade &upgrade : upgrades) value += std::ceil(baseValue * upgrade.modifierName); \
															return value;

Component::Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager)
	: id(componentId), manager(componentManager), integrity(getMaxIntegrity()) {}

const ComponentInfo &Component::fetchInfo() {
	return manager->get(id);
}

void Component::yourTurn() {
	if (isEnabled()) {
		increaseHeat(getPassiveHeat());

		yourTurnEnabled();
	}

	if (disabledForTurns > 0)
		disabledForTurns--;

	if (heat >= getFatalHeatLevel() && Random::percentageChange(80)) // If at a fatal heat level then there is an 80% chance that the component will become disabled.
		disabledForTurns += Random::integerRange(2, 3);
	else if (heat >= getDangerousHeatLevel() && Random::percentageChange(50)) // If at a dangerous heat level then the chance is 50% of becoming disabled.
		disabledForTurns += Random::integerRange(1, 2);
}

void Component::yourTurnEnabled() {}

std::vector<ProjectileArc> Component::use(Entity &user, MovementPath path, Console &console) {
	if (isEnabled()) {
		increaseHeat(getUseHeat());
		//increasePower(getUsePower());

		return useEnabled(user, path, console);
	}

	return std::vector<ProjectileArc>();
}

std::vector<ProjectileArc> Component::useEnabled(Entity &user, MovementPath path, Console &console) {
	return std::vector<ProjectileArc>();
}

std::string Component::getName() {
	return fetchInfo().name;
}

std::string Component::getDescription() {
	return fetchInfo().description;
}

unsigned int Component::getIntegrity() {
	return integrity;
}
unsigned int Component::getHeatLevel() {
	return heat;
}
unsigned int Component::getMaxIntegrity() {
	RETURN_VALUE_WITH_UPGRADES(maxIntegrity, maxIntegrityModifier);
}
unsigned int Component::getDangerousHeatLevel() {
	RETURN_VALUE_WITH_UPGRADES(dangerousHeatLevel, unsafeHeatLevelModifier);
}
unsigned int Component::getFatalHeatLevel() {
	RETURN_VALUE_WITH_UPGRADES(fatalHeatLevel, unsafeHeatLevelModifier);
}
unsigned int Component::getPassivePowerGeneration() {
	RETURN_VALUE_WITH_UPGRADES(passivePowerGen, powerModifier);
}
unsigned int Component::getPassivePowerConsumption() {
	RETURN_VALUE_WITH_UPGRADES(passivePowerConsume, powerModifier);
}
unsigned int Component::getUsePowerGeneration() {
	RETURN_VALUE_WITH_UPGRADES(usePowerGen, powerModifier);
}
unsigned int Component::getUsePowerConsumption() {
	RETURN_VALUE_WITH_UPGRADES(usePowerConsume, powerModifier);
}
int Component::getPassiveHeat() {
	RETURN_VALUE_WITH_UPGRADES(passiveHeat, heatModifier);
}
int Component::getUseHeat() {
	RETURN_VALUE_WITH_UPGRADES(useHeat, heatModifier);
}
unsigned int Component::getPowerStorage() {
	RETURN_VALUE_WITH_UPGRADES(powerStorage, powerModifier);
}
std::vector<IDs::ComponentUpgrades> Component::getPossibleUpgrades() {
	return fetchInfo().possibleUpgrades;
}

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
	if (Random::percentageChange(disruption)) {
		int disableFor = Random::integerRange(1, 2);
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

void Component::increaseHeat(int amount) {
	heat += amount;

	if (heat < 0) heat = 0;
}

MovementPath Component::buildProjectilePath(sf::Vector2u source, sf::Vector2u target, GameMap *map) {
	return MovementPath(source); // A regular component can only be used on itself.
}

void Component::toggleManualEnable() {
	manualEnable = !manualEnable;
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