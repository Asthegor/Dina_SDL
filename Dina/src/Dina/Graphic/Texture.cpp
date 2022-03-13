#include "dinapch.h"
#include "Texture.h"

namespace Dina
{
	Texture::Texture() :
		m_Texture(nullptr), m_OriginalDimensions(new Quad),
		m_Dimensions(new Quad), m_Origin(new Point)
	{
		DINA_CORE_ASSERT(m_Texture != nullptr, "The texture must not be null");
	}

	Texture::Texture(SDL_Texture* texture, int x, int y) :
		m_Texture(texture), m_Origin(new Point)
	{
		DINA_CORE_ASSERT(m_Texture,"The texture must not be null");

		m_OriginalDimensions = new Quad{ x,y };
		SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_OriginalDimensions->width, &m_OriginalDimensions->height);
		m_Dimensions = new Quad(*m_OriginalDimensions);
	}
	Texture::Texture(const char* textureName, int x, int y) :
		Texture { Graphic::LoadTexture(textureName), x, y }
	{
	}
	Texture::Texture(const Texture& texture)
	{
		SetDimensions(*texture.GetDimensions());
		SetAngle(texture.GetAngle());
		SetFlip(texture.GetFlip());
		SetOrigin(texture.GetOrigin());
		m_OriginalDimensions = new Quad(*(texture.GetDimensions()));
		SDL_QueryTexture((SDL_Texture*)this, nullptr, nullptr, &m_OriginalDimensions->width, &m_OriginalDimensions->height);
	}

	SDL_Texture* Texture::GetTexture() const
	{
		return m_Texture;
	}

	Quad* Texture::GetDimensions() const
	{
		return m_Dimensions;
	}

	Point* Texture::GetOrigin() const
	{
		return m_Origin;
	}

	SDL_RendererFlip Texture::GetFlip() const
	{
		return m_Flip;
	}

	double Texture::GetAngle() const
	{
		return m_Angle;
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

	void Texture::SetAngle(double angle)
	{
		m_Angle = angle;
	}

	void Texture::SetOrigin(Point* point)
	{
		if (point)
		{
			if (!m_Origin)
				m_Origin = new Point;
			m_Origin->x = point->x;
			m_Origin->y = point->y;
		}
		else
		{
			if (m_Origin)
				delete m_Origin;
			m_Origin = nullptr;
		}
	}

	void Texture::SetFlip(SDL_RendererFlip flip)
	{
		m_Flip = flip;
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
		delete m_Origin;

		SDL_DestroyTexture(m_Texture);
	}

	Point::operator SDL_Point* () const
	{
		SDL_Point* const sdlpt = new SDL_Point;
		sdlpt->x = x;
		sdlpt->y = y;
		return sdlpt;
	}
	FPoint::operator SDL_FPoint* () const
	{
		SDL_FPoint* const sdlfpt = new SDL_FPoint;
		sdlfpt->x = x;
		sdlfpt->y = y;
		return sdlfpt;
	}
}