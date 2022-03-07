#include "dinapch.h"
#include "Random.h"

#include <random>

namespace Dina
{
	Random* Random::m_Instance = nullptr;

	int Random::GetValue(int minValue, int maxValue)
	{
		int min, max;
		if (minValue > maxValue)
		{
			min = maxValue;
			max = minValue;
		}
		else
		{
			max = maxValue;
			min = minValue;
		}
		std::uniform_int_distribution<int> uniform_dist_rows(min, max);
		return uniform_dist_rows(GetInstance()->m_RandomEngine);
	}
	double Random::GetValue(double minValue, double maxValue)
	{
		double min, max;
		if (minValue > maxValue)
		{
			min = maxValue;
			max = minValue;
		}
		else
		{
			max = maxValue;
			min = minValue;
		}
		std::uniform_real_distribution<double> uniform_dist_rows(min, max);
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