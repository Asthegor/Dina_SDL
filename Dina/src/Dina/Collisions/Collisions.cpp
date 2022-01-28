#include "dinapch.h"
#include "Collisions.h"

namespace Dina
{
	bool Collisions::Collide(Point point, Quad quad)
	{
		return quad.x < point.x && quad.x + quad.width > point.x
			&& quad.y < point.y && quad.y + quad.height > point.y;
	}
}