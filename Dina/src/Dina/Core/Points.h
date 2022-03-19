#pragma once
#include <SDL.h>

namespace Dina
{

	struct DINA_API Point
	{
		int x;
		int y;
		Point(int x = 0, int y = 0) : x(x), y(y)
		{}
		operator SDL_Point* () const;
	};
	struct DINA_API FPoint
	{
		float x;
		float y;
		FPoint(float x = 0.0f, float y = 0.0f) : x(x), y(y)
		{}
		operator SDL_FPoint* () const;
	};
}