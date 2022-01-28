#include "dinapch.h"
#include "Random.h"

#include <random>

namespace Dina
{
	Random* Random::m_Instance = nullptr;

	int Random::GetValue(int minValue, int maxValue)
	{
		std::uniform_int_distribution<int> uniform_dist_rows(minValue, maxValue);
		return uniform_dist_rows(GetInstance()->m_RandomEngine);
	}
	Random::Random()
	{
		std::random_device rd;
		m_RandomEngine = std::mt19937{ rd() };
	}
	Random* Random::GetInstance()
	{
		if (!m_Instance)
			m_Instance = new Random;
		return m_Instance;
	}
}