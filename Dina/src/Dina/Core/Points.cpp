#include "dinapch.h"
#include "Points.h"

namespace Dina
{
	Point::operator SDL_Point* () const
	{
		SDL_Point* const sdlpt = new SDL_Point;
		sdlpt->x = x;
		sdlpt->y = y;
		return sdlpt;
	}
	FPoint::operator SDL_FPoint* () const
	{
		SDL_FPoint* const sdlfpt = new SDL_FPoint;
		sdlfpt->x = x;
		sdlfpt->y = y;
		return sdlfpt;
	}
}