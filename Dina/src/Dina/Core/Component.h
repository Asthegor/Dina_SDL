#pragma once

#include "Dina/Events/Events.h"
#include <SDL.h>

namespace Dina
{
	class DINA_API Component : public Event
	{
	public:
		virtual ~Component()
		{}
		virtual void Update(double deltatime) = 0;
		virtual void Draw() = 0;
		virtual void Load() = 0;

	protected:
		SDL_Renderer* renderer;

	};
}