#pragma once
#include <random>

namespace Dina
{

	class DINA_API Random
	{
	public:
		static int GetValue(int minValue, int maxValue);

	private :
		Random();
		static Random* GetInstance();
		static Random* m_Instance;

		std::mt19937 m_RandomEngine;
	};
}