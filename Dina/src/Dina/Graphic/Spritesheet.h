#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Quad.h"

namespace Dina
{

	class DINA_API Spritesheet
	{
	public:
		Spritesheet(const char* fileName, int tileWidth, int tileHeight);

		~Spritesheet();

		Sprite* GetSprite(int num);

		int GetNbSprites() const;

	private:
		Texture* m_Texture = nullptr;
		std::vector<Sprite*> m_Sprites;
	};

}
