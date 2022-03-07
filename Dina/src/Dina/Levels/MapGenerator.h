#pragma once
#include "Dina/Core/Component.h"
#include "Dina/Graphic/Graphic.h"
#include "Dina/Graphic/Quad.h"

#include "Dina/Utils/Utils.h"
#include "Dina/Utils/Random.h"

#include "Dina/Utils/noise1234.h"

namespace Dina
{

	class DINA_API MapGenerator : public Component
	{
		float m_Seed = 0.0f;
		const float m_Scale = 75.0f;
		const int m_DrawScale = 100;
		Noise1234 m_Noise1234;

		SDL_Surface* m_Surface = nullptr;
		Point* m_SurfaceOrigin = nullptr;
		double* m_NoisePoints = nullptr;

		int m_LargeurIle;
		int m_HauteurIle;

	public:
		~MapGenerator();

		void Load() override;
		void Update(double deltatime) override;
		void Draw() override;

		void Generate();


		void OnKeyPressed(KeyCode key);
	};

}