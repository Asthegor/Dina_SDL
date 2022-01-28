#pragma once

namespace Dina
{
	struct Point
	{
		int x;
		int y;
	};

	struct Collisions
	{
		static bool Collide(Point point, Quad quad);
	};

}