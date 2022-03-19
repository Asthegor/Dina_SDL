#pragma once
#include "Dina/Core/Points.h"

namespace Dina
{
	class Maths
	{
	public:
		template <typename T>
		static T Normalize(T value, T min, T max)
		{
			return (value - min) / (max - min);
		}

		template <typename T>
		static T Distance(T x1, T y1, T x2, T y2)
		{
			return static_cast<T>(sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
		}

		
		static FPoint Direction(FPoint origin, FPoint destination)
		{
			float dx = destination.x - origin.x;
			float dy = destination.y - origin.y;
			float d = std::sqrt(dx * dx + dy * dy);
			return { dx / d, dy / d };
		}
		static Point Direction(Point origin, Point destination)
		{
			int dx = destination.x - origin.x;
			int dy = destination.y - origin.y;
			double d = std::sqrt(dx * dx + dy * dy);
			return { static_cast<int>(dx / d), static_cast<int>(dy / d) };
		}
	};
}