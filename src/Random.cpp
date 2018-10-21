#include "Random.h"

std::uniform_real_distribution<float> Random::percentDistribution(0.0f, 100.0f);

Random::Random() : rand() {}
Random::Random(unsigned int seed) : rand(seed) {}

bool Random::percentageChange(float likelyhood) {
	return likelyhood >= percentDistribution(rand);
}

int Random::integerRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(rand);
}

float Random::floatRange(float min, float max) {
	return std::uniform_real_distribution<float>(min, max)(rand);
}
