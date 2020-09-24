#include "zpch.hpp"
#include "Random.hpp"

#include <random>

namespace ZEngine {

	unsigned int Random::s_Seed = 0;

	void Random::Init()
	{
		s_Seed = 5; // TODO: GetTime

		std::random_device seeder;
		std::mt19937 engine(seeder());
	}

	void Random::Init(unsigned int seed)
	{
		s_Seed = seed;
		std::mt19937 rng(seed);
	}

	int Random::RandomInt(int min /*= 0*/, int max /*= 0x7FFF*/)
	{
		s_Seed = (214013 * s_Seed + 2531011);
		return ((s_Seed >> 16) & 0x7FFF) % (max - min + 1) + min;
	}
}