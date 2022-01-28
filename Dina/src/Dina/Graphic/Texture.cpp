#include "dinapch.h"
#include "Texture.h"
#include "Graphic.h"

namespace Dina
{
	Texture::Texture() :
		m_Texture(nullptr), m_OriginalDimensions(new Dina::Quad),
		m_Dimensions(new Dina::Quad)
	{}

	Texture::Texture(SDL_Texture* texture, int x, int y) :
		m_Texture(texture)
	{
		m_OriginalDimensions = new Dina::Quad{ x,y };
		SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_OriginalDimensions->width, &m_OriginalDimensions->height);
		m_Dimensions = new Dina::Quad(*m_OriginalDimensions);
	}
	Texture::Texture(const char* textureName, int x, int y) :
		Texture { Graphic::LoadTexture(textureName), x, y }
	{
	}
	Texture::Texture(const Texture& texture)
	{
		SetDimensions(*texture.GetDimensions());

		m_OriginalDimensions = new Dina::Quad(*(texture.GetDimensions()));
		SDL_QueryTexture(GetTexture(), nullptr, nullptr, &m_OriginalDimensions->width, &m_OriginalDimensions->height);
	}

	SDL_Texture* Texture::GetTexture() const
	{
		return m_Texture;
	}

	Dina::Quad* Texture::GetDimensions() const
	{
		return m_Dimensions;
	}

	void Texture::SetPosition(int x, int y)
	{
		m_Dimensions->x = x;
		m_Dimensions->y = y;
	}

	void Texture::SetSize(int width, int height)
	{
		m_Dimensions->width = width;
		m_Dimensions->height = height;
	}

	void Texture::SetDimensions(const Quad newDimensions)
	{
		delete m_Dimensions;
		m_Dimensions = new Quad(newDimensions);
	}

	void Texture::ResetSize()
	{
		m_Dimensions->x = m_OriginalDimensions->x;
		m_Dimensions->y = m_OriginalDimensions->y;
		m_Dimensions->width = m_OriginalDimensions->width;
		m_Dimensions->height = m_OriginalDimensions->height;
	}

	Texture::~Texture()
	{
		delete m_Dimensions;
		delete m_OriginalDimensions;

		SDL_DestroyTexture(m_Texture);
	}
}