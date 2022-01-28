#include "dinapch.h"
#include "Quad.h"

namespace Dina
{
	Quad::Quad(int x, int y, int width, int height) :
		x(x), y(y), width(width), height(height)
	{
	}
	Quad::Quad(const SDL_Rect rect)
	{
		x = rect.x;
		y = rect.y;
		width = rect.w;
		height = rect.h;
	}
	Quad::Quad(const Quad& quad)
	{
		x = quad.x;
		y = quad.y;
		width = quad.width;
		height = quad.height;
	}
	SDL_Rect Quad::ToSDLRect()
	{
		return SDL_Rect{ x, y, width, height };
	}
}