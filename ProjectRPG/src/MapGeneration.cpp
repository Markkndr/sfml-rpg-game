#include "stdafx.h"
#include "MapGeneration.h"

int rnd::randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
	return dist(mt);
}

int rnd::randomInt(int min, int max)
{
	std::uniform_int_distribution<> dist(0, max - min);
	return dist(mt) + min;
}

bool rnd::randomBool(double probability)
{
	std::bernoulli_distribution dist(probability);
	return dist(mt);;
}

void MapGeneration::generate(int maxFeatures)
{
}
