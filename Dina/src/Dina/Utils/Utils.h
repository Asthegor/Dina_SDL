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
	};
}