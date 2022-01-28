#pragma once
#include "Graphic.h"
#include "Quad.h"
#include <SDL.h>


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

		void SetPosition(int x, int y);
		void SetSize(int width, int height);
		void SetDimensions(const Quad dimensions);

		void ResetSize();

		~Texture();

	private:
		SDL_Texture* m_Texture;
		Quad* m_Dimensions;
		Quad* m_OriginalDimensions;
	};

}