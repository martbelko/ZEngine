#pragma once

namespace ZEngine {

	class Random
	{
	public:
		static void Init();
		static void Init(unsigned int seed);

		static int RandomInt(int left = 0, int right = 0x7FFF);
	private:
		static unsigned int s_Seed;
	};

}