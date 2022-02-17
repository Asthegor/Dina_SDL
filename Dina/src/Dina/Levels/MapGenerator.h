#pragma once
#include "Dina/Graphic/Graphic.h"
#include "Dina/Graphic/Quad.h"
#include "Dina/Core/Component.h"
#include "Dina/Utils/SimplexNoise.h"
#include "Dina/Utils/Utils.h"
#include "Dina/Utils/Random.h"
#include <vector>

namespace Dina
{

	class DINA_API MapGenerator : public Component
	{
		float m_Seed = 0.0f;
		const float m_Scale = 75.0f;
	public:

		void Load() override
		{
			m_Seed = static_cast<float>(Random::GetValue(1, 10000));
			Quad* screen = Graphic::GetDimensions();
			
		}
		void Update(double deltatime) override
		{
			m_Seed += static_cast<float>(10.0 * deltatime);
			Generate();
		}
		void Draw() override
		{
			if (m_NoisePoints)
			{
				int scale = 100;
				Quad* screen = Graphic::GetDimensions();
				for (int row = 0; row < screen->height; ++row)
				{
					for (int col = 0; col < screen->width; ++col)
					{
						Graphic::DrawPoint({ col, static_cast<int>(row + m_NoisePoints[row * screen->width + col] * scale) });
					}
				}
			}
		}

		void Generate()
		{
			Quad* screen = Graphic::GetDimensions();
			if (!m_NoisePoints)
				m_NoisePoints = new float[screen->width * screen->height];

			float min = 1.0f;
			float max = -1.0f;
			for (int row = 0; row < screen->height; ++row)
			{
				for (int col = 0; col < screen->width; ++col)
				{
					float noise = SimplexNoise::noise((col + m_Seed) / m_Scale, (row + m_Seed) / m_Scale);
					if (noise < min) min = noise;
					if (noise > max) max = noise;
					m_NoisePoints[row * screen->width + col] = noise;
				}
			}

			for (int row = 0; row < screen->height; ++row)
			{
				for (int col = 0; col < screen->width; ++col)
				{
					m_NoisePoints[row * screen->width + col] = Maths::Normalize(m_NoisePoints[row * screen->width + col], min, max);
				}
			}
		}

	private:
		float* m_NoisePoints = nullptr;

	};

}