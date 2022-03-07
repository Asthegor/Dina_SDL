#include "dinapch.h"
#include "MapGenerator.h"

namespace Dina
{
	MapGenerator::~MapGenerator()
	{
		delete m_SurfaceOrigin;
		delete m_NoisePoints;
	}

	void MapGenerator::Load()
	{
		Quad* screen = Graphic::GetDimensions();
		m_LargeurIle = screen->width * 2;
		m_HauteurIle = screen->height * 2;
		m_SurfaceOrigin = new Point { screen->width / -2 , screen->height / -2 };

		Generate();
	}
	void MapGenerator::Update(double deltatime)
	{
		m_Seed += static_cast<float>(m_DrawScale * deltatime);
		Generate();
	}
	void MapGenerator::Draw()
	{
		Graphic::DrawSurface(m_Surface, m_SurfaceOrigin->x, m_SurfaceOrigin->y);
	}
	void MapGenerator::Generate()
	{
		m_Seed = static_cast<float>(Random::GetValue(1, 10000));
		if (m_NoisePoints)
			delete[] m_NoisePoints;

		Quad* screen = Graphic::GetDimensions();
		m_NoisePoints = new double[m_LargeurIle * m_HauteurIle];


		std::vector<Point> centers;

		int nbSommets = 3;// Random::GetValue(3, 10);

		for (int i = 0; i < nbSommets; ++i)
		{
			centers.push_back({
				static_cast<int>(Random::GetValue(0, m_LargeurIle)),
				static_cast<int>(Random::GetValue(0, m_HauteurIle))
							  });
		}

		if (m_Surface)
			SDL_FreeSurface(m_Surface);
		m_Surface = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			m_LargeurIle, m_HauteurIle, // Sizes
			32, // BPP
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x000000FF,
			0x0000FF00,
			0x00FF0000,
			0xFF000000);
#else
			0xFF000000,
			0x00FF0000,
			0x0000FF00,
			0x000000FF);
#endif

		double min = 10;
		double max = -10;
		double distance = 0.0, ratioX = 0.0, ratioY = 0.0;
		for (int row = 0; row < m_HauteurIle; ++row)
		{
			for (int col = 0; col < m_LargeurIle; ++col)
			{
				//double hauteur = Maths::Normalize(m_NoisePoints[row * m_LargeurIle + col], min, max);
				double noise = m_Noise1234.noise((col + m_Seed) / m_Scale, (row + m_Seed) / m_Scale);
				for (int i = 0; i < nbSommets; ++i)
				{
					distance = Maths::Distance(col, row, centers[i].x, centers[i].y);
					ratioX += distance / centers[i].x;
					ratioY += distance / centers[i].y;
				}
				ratioX /= nbSommets;
				ratioY /= nbSommets;
				double ratio = std::max(ratioX, ratioY);
				noise *= ratio;
				if (noise < min) min = noise;
				if (noise > max) max = noise;
				m_NoisePoints[row * m_LargeurIle + col] = noise;

			}
		}
		for (int row = 0; row < m_HauteurIle; ++row)
		{
			for (int col = 0; col < m_LargeurIle; ++col)
			{
				double hauteur = Maths::Normalize(m_NoisePoints[row * m_LargeurIle + col], min, max);
				Graphic::DrawPointOnSurface(m_Surface, { col, row }, { 255,255,255,static_cast<unsigned char>(hauteur * 255) });
			}
		}
		for (int i = 0; i < nbSommets; ++i)
		{
			Graphic::DrawCircleOnSurface(m_Surface, centers[i], 5, Graphic::ShapeMode::Line, { 255,0,0,255 });
		}
	}
	void MapGenerator::OnKeyPressed(KeyCode key)
	{
		switch (key)
		{
			case KeyCode::Up:
				--m_SurfaceOrigin->y;
				break;
			case KeyCode::Down:
				++m_SurfaceOrigin->y;
				break;
			case KeyCode::Left:
				--m_SurfaceOrigin->x;
				break;
			case KeyCode::Right:
				++m_SurfaceOrigin->x;
				break;
		}
	}
}