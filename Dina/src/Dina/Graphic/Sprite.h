#pragma once
#include "Quad.h"
#include "Texture.h"

namespace Dina
{

	class DINA_API Sprite
	{
	public:
		Sprite(Texture* texture, int x, int y, int width, int height);
		~Sprite();

		SDL_Texture* GetTexture() const;

		Quad* GetImgPosInSheet() const;
		Quad* GetDimensions() const;
		void SetPosition(int x, int y);
		void SetDimensions(const Quad dimensions);


	private:
		Texture* m_Texture = nullptr;
		Quad* m_SpritesheetPosition;
	};

}