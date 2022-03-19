#pragma once
#include "Dina/Core/Points.h"
#include "Dina/Graphic/Quad.h"

namespace Dina
{

	struct DINA_API Collisions
	{
		static bool Collide(Point point, Quad quad);
	};

}