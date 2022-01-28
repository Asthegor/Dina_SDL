#include "dinapch.h"
#include "EventManager.h"
#include <SDL.h>

namespace Dina
{
	EventManager* EventManager::s_Instance = nullptr;

	bool EventManager::Execute()
	{

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EventType::SDL_QUIT:
					return true;

				case SDL_EventType::SDL_KEYDOWN:
					{
						if (GetInstance()->m_LastKeyboardEvent)
							delete GetInstance()->m_LastKeyboardEvent;
						GetInstance()->m_LastKeyboardEvent = new SDL_Event(event);

						if (event.key.repeat == 0)
							GetInstance()->m_KeyPressed = true;
						else
							GetInstance()->m_KeyRepeat = true;

						break;
					}
				case SDL_EventType::SDL_KEYUP:
					{
						GetInstance()->m_KeyPressed = false;
						auto keyboardEventCallback = dynamic_cast<KeyboardEvent*>(GetInstance()->m_EventCallback);
						if (keyboardEventCallback)
							keyboardEventCallback->OnKeyReleased(static_cast<KeyCode>(event.key.keysym.sym));
						break;
					}
				case SDL_EventType::SDL_MOUSEMOTION:
					{
						auto mouseEventCallback = dynamic_cast<MouseEvent*>(GetInstance()->m_EventCallback);
						if (mouseEventCallback)
							mouseEventCallback->OnMouseMove(event.motion.x, event.motion.y);
						break;
					}
				case SDL_EventType::SDL_MOUSEBUTTONDOWN:
					{
						GetInstance()->m_MousePressed = true;
						if (GetInstance()->m_LastMouseEvent)
							delete GetInstance()->m_LastMouseEvent;
						GetInstance()->m_LastMouseEvent = new SDL_Event(event);
						break;
					}
				case SDL_EventType::SDL_MOUSEBUTTONUP:
					{
						GetInstance()->m_MousePressed = false;
						auto mouseEventCallback = dynamic_cast<MouseEvent*>(GetInstance()->m_EventCallback);
						if (mouseEventCallback)
							mouseEventCallback->OnMouseReleased(event.button.button, event.button.x, event.button.y);
						break;
					}
			}
		}

		if (GetInstance()->m_LastKeyboardEvent)
		{
			auto keyboardEvent = *GetInstance()->m_LastKeyboardEvent;
			auto keyboardEventCallback = dynamic_cast<KeyboardEvent*>(GetInstance()->m_EventCallback);
			if (keyboardEventCallback)
			{
				if (GetInstance()->m_KeyPressed)
					keyboardEventCallback->OnKeyPressed(static_cast<KeyCode>(keyboardEvent.key.keysym.sym));
				if (GetInstance()->m_KeyRepeat)
					keyboardEventCallback->OnKeyRepeat(static_cast<KeyCode>(keyboardEvent.key.keysym.sym));
			}
		}
		if (GetInstance()->m_MousePressed && GetInstance()->m_LastMouseEvent)
		{
			auto mouseEvent = *GetInstance()->m_LastMouseEvent;
			auto mouseEventCallback = dynamic_cast<MouseEvent*>(GetInstance()->m_EventCallback);
			if (mouseEventCallback)
				mouseEventCallback->OnMousePressed(mouseEvent.button.button, mouseEvent.button.x, mouseEvent.button.y, mouseEvent.button.clicks);
		}

		return false;
	}

	bool EventManager::Subscribe(Event* event)
	{
		if (event && GetInstance()->Unsubscribe(event))
			GetInstance()->m_EventCallback = event;
		else
			DINA_CORE_WARN("You must unsubscribe the previous event before subscribing for a new one.");

		return GetInstance()->m_EventCallback == event;
	}

	bool EventManager::Unsubscribe(Event* event)
	{
		if (event == GetInstance()->m_EventCallback)
		{
			GetInstance()->m_KeyPressed = false;
			delete GetInstance()->m_LastKeyboardEvent;
			GetInstance()->m_LastKeyboardEvent = nullptr;

			GetInstance()->m_MousePressed = false;
			delete GetInstance()->m_LastMouseEvent;
			GetInstance()->m_LastMouseEvent = nullptr;


			GetInstance()->m_EventCallback = nullptr;
		}
		else if(GetInstance()->m_EventCallback)
			DINA_CORE_WARN("The given event is not the current event callback.");

		return GetInstance()->m_EventCallback == nullptr;
	}

	void EventManager::QuitGame()
	{
		SDL_Event sdlevent {};
		sdlevent.type = SDL_QUIT;
		sdlevent.key.keysym.sym = SDLK_ESCAPE;
		SDL_PushEvent(&sdlevent);
	}

	EventManager::EventManager() : m_EventCallback(nullptr)
	{}

	EventManager::~EventManager()
	{
		EventManager::Unsubscribe(GetInstance()->m_EventCallback);
	}

	EventManager* EventManager::GetInstance()
	{
		if (!s_Instance)
			s_Instance = new EventManager;

		return s_Instance;
	}

}