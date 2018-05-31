#include "Component.h"

Component::Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager)
	: id(componentId), rand(std::random_device()()), manager(componentManager), integrity(getMaxIntegrity()) {}

const ComponentInfo &Component::fetchInfo() {
	return manager->get(id);
}

void Component::yourTurn() {
	if (isEnabled())
		yourTurnEnabled();

	if (disabledForTurns > 0)
		disabledForTurns--;
}

void Component::yourTurnEnabled() {}

bool Component::use() {
	return true;
}

std::string Component::getName() {
	return fetchInfo().name;
}

std::string Component::getDescription() {
	return fetchInfo().description;
}

int Component::getIntegrity() {
	return integrity;
}

int Component::getMaxIntegrity() {
	int baseMaxIntegrity = fetchInfo().maxIntegrity;
	int maxIntegrity = baseMaxIntegrity;

	for (const ComponentUpgrade &upgrade : upgrades) {
		maxIntegrity += static_cast<int>(baseMaxIntegrity * upgrade.maxIntegrityModifier);
	}

	return maxIntegrity;
}

int Component::getHeatLevel() {
	return heat;
}

int Component::getDangerousHeatLevel() {
	int baseDangerousHeatLevel = fetchInfo().dangerousHeatLevel;
	int dangerousHeatLevel = baseDangerousHeatLevel;

	for (const ComponentUpgrade &upgrade : upgrades) {
		dangerousHeatLevel += static_cast<int>(baseDangerousHeatLevel * upgrade.dangerousHeatLevelModifier);
	}

	return dangerousHeatLevel;
}

int Component::getFatalHeatLevel() {
	int baseFatalHeatLevel = fetchInfo().fatalHeatLevel;
	int fatalHeatLevel = baseFatalHeatLevel;

	for (const ComponentUpgrade &upgrade : upgrades) {
		fatalHeatLevel += static_cast<int>(baseFatalHeatLevel * upgrade.fatalHeatLevelModifier);
	}

	return fatalHeatLevel;
}

int Component::getPassivePowerDrain() {
	int basePassivePowerDrain = fetchInfo().passivePowerDrain;
	int passivePowerDrain = basePassivePowerDrain;

	for (const ComponentUpgrade &upgrade : upgrades) {
		passivePowerDrain += static_cast<int>(basePassivePowerDrain * upgrade.passivePowerDrainModifer);
	}

	return passivePowerDrain;
}

std::vector<IDs::ComponentUpgrades> Component::getPossibleUpgrades() {
	return fetchInfo().possibleUpgrades;
}

sf::Vector2f Component::getIconTextureSize() {
	return manager->getSingleIconTextureSize();
}

void Component::applyDamage(Damage damage) {
	applyKineticDamage(damage.kinetic);
	applyThermalDamage(damage.thermal);
	applyDisruption(damage.disruption);
}

void Component::applyKineticDamage(int damage) {
	reduceIntegrity(damage);
}
void Component::applyThermalDamage(int heat) {
	increaseHeat(heat);
}
void Component::applyDisruption(float disruption) {
	std::uniform_real_distribution<float> chanceDist(0.0, 1.0);
	std::uniform_int_distribution<int> turnsMissedDist(2, 3);

	if (chanceDist(rand) <= disruption) {
		disabledForTurns += turnsMissedDist(rand);
	}
}

void Component::increaseIntegrity(int amount) {
	integrity += amount;

	if (integrity > getMaxIntegrity())
		integrity = getMaxIntegrity();
}

void Component::reduceIntegrity(int amount) {
	integrity -= amount;
}

void Component::increaseHeat(int amount) {
	heat += amount;

	if (heat >= getFatalHeatLevel()); // TODO: ...
	else if (heat >= getDangerousHeatLevel()); // ...
}

void Component::reduceHeat(int amount) {
	heat -= amount;

	if (heat < 0)
		heat = 0;
}

int Component::reduceHeatByPercentage(float percentage) {
	int amount = static_cast<int>(heat * percentage);
	reduceHeat(amount);
	return amount;
}

bool Component::isDestroyed() {
	return integrity <= 0;
}

bool Component::isEnabled() {
	return disabledForTurns <= 0 && enabled;
}

sf::Color Component::getColour() {
	// TODO: Implement component colours!
	return sf::Color(80, 255, 80, 255);
}