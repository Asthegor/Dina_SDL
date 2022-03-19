#pragma once
#include "Quad.h"
#include <SDL.h>
#include "Dina/Core/Points.h"

namespace Dina
{

	class DINA_API Texture
	{
	public:
		Texture();
		Texture(SDL_Texture* texture, int x = 0, int y = 0);
		Texture(const char* textureName, int x = 0, int y = 0);
		Texture(const Texture& texture);


		SDL_Texture* GetTexture() const;
		Quad* GetDimensions() const;
		double GetAngle() const;
		Point* GetOrigin() const;
		SDL_RendererFlip GetFlip() const;

		void SetPosition(int x, int y);
		void SetSize(int width, int height);
		void SetDimensions(const Quad dimensions);
		void SetAngle(double angle);
		void SetOrigin(Point* point);
		void SetFlip(SDL_RendererFlip flip);

		void ResetSize();

		~Texture();

	private:
		SDL_Texture* m_Texture;
		Quad* m_Dimensions;
		Quad* m_OriginalDimensions;
		Point* m_Origin;
		double m_Angle = 0.0;
		SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
	};

}