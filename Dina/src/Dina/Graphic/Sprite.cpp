#include "dinapch.h"
#include "Sprite.h"
#include "Texture.h"

namespace Dina
{
	Sprite::Sprite(Texture* texture, int x, int y, int width, int height) :
		m_Texture(texture),
		m_SpritesheetPosition(new Quad { x, y, width, height })
	{
		Quad* quad = m_Texture->GetDimensions();
		m_Texture->SetDimensions({ quad->x, quad->y, width, height });
	}
	Sprite::~Sprite()
	{
		delete m_SpritesheetPosition;
	}
	Texture* Sprite::GetTexture() const
	{
		return m_Texture;
	}
	Quad* Sprite::GetImgPosInSheet() const
	{
		return m_SpritesheetPosition;
	}
	
	Quad* Sprite::GetDimensions() const
	{
		return m_Texture->GetDimensions();
	}
	void Sprite::SetPosition(int x, int y)
	{
		m_Texture->SetPosition(x, y);
	}
	void Sprite::SetDimensions(const Quad dimensions)
	{
		m_Texture->SetDimensions(dimensions);
	}
}