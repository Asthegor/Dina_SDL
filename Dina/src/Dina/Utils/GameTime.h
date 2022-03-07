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
	class Chrono
	{
	public:
		Chrono() :
			m_PauseChrono(new Chrono)
		{
		}

		void Start()
		{
			m_BeginTime = std::chrono::steady_clock::now();
		}
		void Pause()
		{
			if (!m_IsStart)
			{
				Start();
			}
			else
			{
				if (m_PauseChrono->IsActive())
				{
					m_PauseChrono->Stop();
					auto pauseTime = std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>(m_PauseChrono->GetTime()));
					m_BeginTime += pauseTime;
					delete m_PauseChrono;
					m_PauseChrono = nullptr;
				}
				else
				{
					m_PauseChrono->Start();
				}
			}
		}
		void Stop()
		{
			if (m_IsStart && !m_IsStop)
			{
				m_ElapsedTime = std::chrono::steady_clock::now();
				m_IsStart = false;
				m_IsStop = true;
			}
		}

		double GetTime()
		{
			if (!m_IsPaused)
			{
				Stop();
				std::chrono::duration<double> deltatime = m_ElapsedTime - m_BeginTime;
				return deltatime.count();
			}
			return -1.0;
		}
	private:
		bool IsActive()
		{
			return m_IsStart && !m_IsPaused && !m_IsStop;
		}

		bool m_IsStart = false;
		bool m_IsStop = false;
		bool m_IsPaused = false;
		Timer m_BeginTime;
		Timer m_ElapsedTime;
		Chrono* m_PauseChrono;
	};
}