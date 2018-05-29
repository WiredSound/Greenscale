#include "Component.h"

Component::Component(IDs::Components componentId, std::shared_ptr<ComponentManager> componentManager)
	: id(componentId), rand(std::random_device()()), manager(componentManager) {}

const ComponentInfo &Component::fetchInfo() {
	return manager->get(id);
}

void Component::yourTurn() {
	if (disabledForTurns > 0)
		disabledForTurns--;
}

std::string Component::getName() {
	return fetchInfo().name;
}
std::string Component::getDescription() {
	return fetchInfo().description;
}
int Component::getMaxIntegrity() {
	int baseMaxIntegrity = fetchInfo().maxIntegrity;
	// TODO: Apply upgrade modifiers...
	return baseMaxIntegrity;
}
int Component::getDangerousHeatLevel() {
	int baseDangerousHeatLevel = fetchInfo().dangerousHeatLevel;
	// TODO: Apply upgrade modifiers...
	return baseDangerousHeatLevel;
}
int Component::getFatalHeatLevel() {
	int baseFatalHeatLevel = fetchInfo().fatalHeatLevel;
	// TODO: Apply upgrade modifiers...
	return baseFatalHeatLevel;
}

std::vector<IDs::ComponentUpgrades> Component::getPossibleUpgrades() {
	return std::vector<IDs::ComponentUpgrades>(); // TODO: Fix this!
	//return fetchInfo().possibleUpgrades;
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
	int amount = heat * percentage;
	reduceHeat(amount);
	return amount;
}

bool Component::isDestroyed() {
	return integrity <= 0;
}

sf::Color Component::getColour() {
	// TODO: Implement component colours!
	return sf::Color(80, 255, 80, 255);
}