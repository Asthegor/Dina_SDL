#include "dinapch.h"
#include "Font.h"

namespace Dina
{
	Font::Font(const char* text, const char* fontName, int fontSize, FontRender fontRender, SDL_Color color, SDL_Color backgroundcolor) :
		m_Text(text), m_Size(fontSize), m_Font(nullptr), m_FontRender(fontRender), m_Color(color), m_BackgroundColor(backgroundcolor), m_Surface(nullptr)
	{

		m_Font = TTF_OpenFont(fontName, m_Size);
		if (!m_Font)
		{
			DINA_CORE_ERROR("Unable to create the font. Error: {0}", TTF_GetError());
		}

	}

	SDL_Surface* Font::GetSurface()
	{
		if(!m_Surface)
		{
			CreateSurface();
		}
		return m_Surface;
	}

	void Font::CreateSurface()
	{
		if (!m_Font)
			return;

		switch (m_FontRender)
		{
			case FontRender::Solid:
			{
				if (!(m_Surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color)))
				{
					DINA_CORE_ERROR("Unable to create font surface. Error: {0}", TTF_GetError());
					m_Surface = nullptr;
				}
			}
			break;
			case FontRender::Shaded:
			{
				if (!(m_Surface = TTF_RenderText_Shaded(m_Font, m_Text.c_str(), m_Color, m_BackgroundColor)))
				{
					DINA_CORE_ERROR("Unable to create font surface. Error: {0}", TTF_GetError());
					m_Surface = nullptr;
				}
			}
			break;
			case FontRender::Blended:
			{
				if (!(m_Surface = TTF_RenderText_Blended(m_Font, m_Text.c_str(), m_Color)))
				{
					DINA_CORE_ERROR("Unable to create font surface. Error: {0}", TTF_GetError());
					m_Surface = nullptr;
				}
			}
			break;
		}
	}

	Font::~Font()
	{
		TTF_CloseFont(m_Font);
		m_Font = nullptr;
	}

}