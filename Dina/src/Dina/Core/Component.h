#pragma once

#include "Dina/Events/Events.h"
#include <SDL.h>

namespace Dina
{
	class DINA_API Component : public Event
	{
	public:
		Component() = default;
		virtual ~Component() = default;
		virtual void Load() = 0;
		virtual void Update(double deltatime) = 0;
		virtual void Draw() = 0;
	private:
	};
}