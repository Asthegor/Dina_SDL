#pragma once

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
	};
}