#include "Component.h"

Component::Component(IDs::Components componentId, ComponentManager &componentManager)
	: id(componentId), manager(componentManager), rand(std::random_device()()) {}

const ComponentInfo &Component::fetchInfo() {
	return manager.get(id);
}

void Component::yourTurn() {
	if (disabledForTurns > 0)
		disabledForTurns--;
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

	if (integrity > fetchInfo().maxIntegrity)
		integrity = fetchInfo().maxIntegrity;
}

void Component::reduceIntegrity(int amount) {
	integrity -= amount;
}

void Component::increaseHeat(int amount) {
	heat += amount;

	if (heat >= fetchInfo().fatalHeatLevel); // TODO: ...
	else if (heat >= fetchInfo().dangerousHeatLevel);
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