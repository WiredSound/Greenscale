#include "FpsCounter.h"

FpsCounter::FpsCounter(sf::Time recordFreq) : interval(recordFreq) {
	clock.restart();
}

void FpsCounter::update() {
	counter++;

	if (clock.getElapsedTime() > interval) {
		clock.restart();

		fps = counter * (1000.0f / interval.asMilliseconds());
		counter = 0;
	}
}

unsigned int FpsCounter::get() {
	return fps;
}