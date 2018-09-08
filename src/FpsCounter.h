#pragma once

#include <SFML/System/Clock.hpp>

class FpsCounter {
public:
	FpsCounter(sf::Time recordFreq);
	void update();
	unsigned int get();

private:
	unsigned int fps = 0;
	unsigned int counter = 0;
	sf::Clock clock;
	sf::Time interval;
};