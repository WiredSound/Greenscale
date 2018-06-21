#include "Component.h"

Component::Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager)
	: id(componentId), rand(std::random_device()()), manager(componentManager), integrity(getMaxIntegrity()), randomTurnsMissed(1, 3), randomPercentage(0, 100) {}

const ComponentInfo &Component::fetchInfo() {
	return manager->get(id);
}

void Component::yourTurn() {
	increaseHeat(getPassiveHeat());

	if (isEnabled())
		yourTurnEnabled();

	if (disabledForTurns > 0)
		disabledForTurns--;

	if (heat >= getFatalHeatLevel() && randomPercentage(rand) >= 80) // If at a fatal heat level then there is an 80% chance that the component will become disabled.
		disabledForTurns += randomTurnsMissed(rand);
	else if (heat >= getDangerousHeatLevel() && randomPercentage(rand) >= 50) // If at a dangerous heat level then the chance is 50% of becoming disabled.
		disabledForTurns += randomTurnsMissed(rand);
}

void Component::yourTurnEnabled() {}

bool Component::use() {
	if (isEnabled()) {
		increaseHeat(getUseHeat());

		return useEnabled();
	}

	return true;
}

bool Component::useEnabled() {
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
		dangerousHeatLevel += static_cast<int>(baseDangerousHeatLevel * upgrade.unsafeHeatLevelModifier);
	}

	return dangerousHeatLevel;
}

int Component::getFatalHeatLevel() {
	int baseFatalHeatLevel = fetchInfo().fatalHeatLevel;
	int fatalHeatLevel = baseFatalHeatLevel;

	for (const ComponentUpgrade &upgrade : upgrades) {
		fatalHeatLevel += static_cast<int>(baseFatalHeatLevel * upgrade.unsafeHeatLevelModifier);
	}

	return fatalHeatLevel;
}

int Component::getPassivePower() {
	int basePassivePower = fetchInfo().passivePower;
	int passivePower = basePassivePower;

	for (const ComponentUpgrade &upgrade : upgrades) {
		passivePower += static_cast<int>(basePassivePower * upgrade.powerModifier);
	}

	return passivePower;
}

int Component::getUsePower() {
	int baseUsePower = fetchInfo().usePower;
	int usePower = baseUsePower;

	for (const ComponentUpgrade &upgrade : upgrades) {
		usePower += static_cast<int>(baseUsePower * upgrade.powerModifier);
	}

	return usePower;
}

int Component::getPassiveHeat() {
	int basePassiveHeat = fetchInfo().passiveHeat;
	int passiveHeat = basePassiveHeat;

	for (const ComponentUpgrade &upgrade : upgrades) {
		passiveHeat += static_cast<int>(basePassiveHeat * upgrade.heatModifier);
	}

	return passiveHeat;
}

int Component::getUseHeat() {
	int baseUseHeat = fetchInfo().useHeat;
	int useHeat = baseUseHeat;

	for (const ComponentUpgrade &upgrade : upgrades) {
		useHeat += static_cast<int>(baseUseHeat * upgrade.heatModifier);
	}

	return useHeat;
}

int Component::getPowerStorage() {
	int basePowerStorage = fetchInfo().powerStorage;
	int powerStorage = basePowerStorage;

	for (const ComponentUpgrade &upgrade : upgrades) {
		powerStorage += static_cast<int>(powerStorage * upgrade.powerModifier);
	}

	return powerStorage;
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

	if (heat < 0) heat = 0;
}

/*
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
*/

void Component::toggleManualEnable() {
	manualEnable = !manualEnable;
}

bool Component::isDestroyed() {
	return integrity <= 0;
}

bool Component::isEnabled() {
	return disabledForTurns <= 0 && manualEnable;
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