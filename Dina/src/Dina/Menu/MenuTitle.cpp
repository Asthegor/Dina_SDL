#include "dinapch.h"
#include "MenuTitle.h"

namespace Dina
{
	MenuTitle::MenuTitle(const char* title, int posY, const char* fontName, int fontSize, SDL_Color color, bool withShadow, int offset, SDL_Color shadowColor)
	{
		m_Title = title;
		m_WithShadow = withShadow;


		m_TitleFont = new Font(title, fontName, fontSize, Dina::FontRender::Blended, color);
		if (m_TitleFont)
		{
			m_TitleTexture = new Texture(Graphic::CreateTextureFromSurface(m_TitleFont->GetSurface()));

			if (m_TitleTexture)
			{
				// Calcul de la position du titre
				Quad* screen = Graphic::GetDimensions();
				Quad* titleRect = m_TitleTexture->GetDimensions();
				m_TitleTexture->SetPosition((screen->width - titleRect->width) / 2, posY);

				if (withShadow)
				{
					m_TitleShadowFont = new Font(title, fontName, fontSize, Dina::FontRender::Blended, shadowColor);
					m_TitleShadowTexture = new Texture(Graphic::CreateTextureFromSurface(m_TitleShadowFont->GetSurface()));
					titleRect = m_TitleTexture->GetDimensions();
					m_TitleShadowTexture->SetPosition(titleRect->x + offset, titleRect->y + offset);
				}
			}
		}
	}

	MenuTitle::~MenuTitle()
	{
		delete m_TitleFont;
		delete m_TitleShadowFont;
		delete m_TitleTexture;
		delete m_TitleShadowTexture;
	}

	void MenuTitle::Draw()
	{
		if (m_TitleTexture)
		{
			if (m_WithShadow && m_TitleShadowTexture)
				Graphic::DrawTexture(m_TitleShadowTexture);

			Graphic::DrawTexture(m_TitleTexture);
		}
	}

}