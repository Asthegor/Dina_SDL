#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Dina
{

	class DINA_API KeyboardEvent
	{
	public:
		virtual ~KeyboardEvent()
		{}
		virtual void OnKeyPressed(KeyCode key)
		{}
		virtual void OnKeyReleased(KeyCode key)
		{}
		virtual void OnKeyRepeat(KeyCode key)
		{}

	};

	struct DINA_API MouseEvent
	{
		virtual ~MouseEvent()
		{}
		virtual void OnMouseMove(int x, int y)
		{}
		virtual void OnMousePressed(int button, int x, int y, int clicks)
		{}
		virtual void OnMouseReleased(int button, int x, int y)
		{}
	};

	class DINA_API Event : public KeyboardEvent, public MouseEvent
	{
	public:
		virtual ~Event(){}
	};
}