#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Quad.h"
#include <vector>
#include "Animation.h"

namespace Dina
{
	class DINA_API Spritesheet
	{
	public:
		Spritesheet(const char* fileName, int tileWidth, int tileHeight);
		Spritesheet(const char* fileName, int tileWidth, int tileHeight, std::vector<int> tileNumbers);

		~Spritesheet();

		Sprite* GetSprite(int num);
		Animation* GetAnimation(std::vector<int> tileNumbers, double frameRate, bool invertDir = false);

		int GetNbSprites() const;

	private:
		Texture* m_Texture = nullptr;
		std::vector<Sprite*> m_Sprites;
	};

}
