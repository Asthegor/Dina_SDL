#include "dinapch.h"
#include "Spritesheet.h"

namespace Dina
{
	Spritesheet::Spritesheet(const char* fileName, int tileWidth, int tileHeight) :
		m_Texture(new Texture(fileName))
	{
		int width = 0, height = 0;
		Quad textureDimensions = *m_Texture->GetDimensions();
		for (int y = 0; y < textureDimensions.height; y += tileHeight)
		{
			for (int x = 0; x < textureDimensions.width; x += tileWidth)
			{
				width = x + tileWidth <= textureDimensions.width ? tileWidth : textureDimensions.width - x;
				height = y + tileHeight <= textureDimensions.height ? tileHeight : textureDimensions.height - y;
				m_Sprites.push_back(new Sprite { m_Texture, x, y, width, height });
			}
		}
	}
	Spritesheet::~Spritesheet()
	{
		delete m_Texture;
		m_Sprites.clear();
	}
	Sprite* Spritesheet::GetSprite(int num)
	{
		if (num >= 0 && num < m_Sprites.size())
			return m_Sprites[num];

		return nullptr;
	}
	int Spritesheet::GetNbSprites() const
	{
		return static_cast<int>(m_Sprites.size());
	}
}