#pragma once
#include "Dina/Graphic/Font.h"
#include "Dina/Graphic/Texture.h"

namespace Dina
{
	class DINA_API MenuTitle
	{
	public:
		MenuTitle(const char* title, const char* fontName, int fontSize, SDL_Color color, bool withShadow, int offset, SDL_Color shadowColor);
		~MenuTitle();

		void Draw();

	private:
		const char* m_Title;
		bool m_WithShadow = false;
		Font* m_TitleFont = nullptr;
		Font* m_TitleShadowFont = nullptr;
		Texture* m_TitleTexture = nullptr;
		Texture* m_TitleShadowTexture = nullptr;
	};

}