#pragma once

#include <random>

class Random {
public:
	Random();
	Random(unsigned int seed);
	bool percentageChange(float likelyhood);
	int integerRange(int min, int max);
	float floatRange(float min, float max);

private:
	std::default_random_engine rand;

	static std::uniform_real_distribution<float> percentDistribution;
};
