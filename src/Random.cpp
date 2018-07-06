#include "Random.h"

std::default_random_engine Random::rand = std::default_random_engine();
std::uniform_real_distribution<float> Random::percentDistribution(0.0f, 100.0f);

bool Random::percentageChange(float likelyhood) {
	return likelyhood >= percentDistribution(rand);
}

int Random::integerRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(rand);
}

float Random::floatRange(float min, float max) {
	return std::uniform_real_distribution<float>(min, max)(rand);
}