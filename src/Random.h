#pragma once

#include <random>

class Random {
public:
	static bool percentageChange(float likelyhood);
	static int integerRange(int min, int max);
	static float floatRange(float min, float max);

private:
	static std::default_random_engine rand;
	static std::uniform_real_distribution<float> percentDistribution;
};