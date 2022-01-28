#pragma once
#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<__int64, std::ratio<1, 1000000000>>> Timer;
namespace Dina
{
	class GameTime
	{

		static GameTime* m_Instance;
		static GameTime* GetInstance();

		Timer lastTime;
	public:


		static double GetElapsedTime();

		~GameTime();
	};
}