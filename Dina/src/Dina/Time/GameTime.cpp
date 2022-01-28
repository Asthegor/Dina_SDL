#include "dinapch.h"
#include "GameTime.h"
#include <chrono>

namespace Dina
{
	GameTime* GameTime::m_Instance = nullptr;

	GameTime* GameTime::GetInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new GameTime;
			m_Instance->lastTime = std::chrono::steady_clock::now();
		}

		return m_Instance;
	}

	double GameTime::GetElapsedTime()
	{
		Timer currentTime = std::chrono::steady_clock::now();
		Timer lastTime = GameTime::GetInstance()->lastTime;
		std::chrono::duration<double> deltatime = currentTime - lastTime;
		GameTime::GetInstance()->lastTime = currentTime;
		return deltatime.count();
	}

	GameTime::~GameTime()
	{
		delete m_Instance;
	}
}