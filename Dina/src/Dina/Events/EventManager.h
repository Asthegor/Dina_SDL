#pragma once
#include "Events.h"
#include <vector>

namespace Dina
{
	class DINA_API EventManager
	{
	public:

		static bool Execute();

		static bool Subscribe(Event* event);
		static bool Unsubscribe(Event* event);

		static void QuitGame();

		EventManager(const EventManager&) = delete;
		EventManager& operator=(const EventManager&) = delete;

	private:
		EventManager();
		~EventManager();

		static EventManager* GetInstance();
		static EventManager* s_Instance;

	private:
		bool m_Quit = false;
		Event* m_EventCallback;

		bool m_MousePressed = false;
		bool m_KeyPressed = false;
		bool m_KeyRepeat = false;
		SDL_Event* m_LastMouseEvent = nullptr;
		SDL_Event* m_LastKeyboardEvent = nullptr;
	};

}