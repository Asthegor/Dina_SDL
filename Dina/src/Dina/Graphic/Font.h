#pragma once
#include <SDL_ttf.h>

namespace Dina
{
	enum class FontRender { Solid = 1, Shaded, Blended };

	class DINA_API Font
	{
	public:
		Font(const char* text, const char* fontName, int fontSize, 
			 FontRender fontRender = FontRender::Solid, 
			 SDL_Color color = { 255, 255, 255, 255 }, SDL_Color backgroundcolor = { 0,0,0,0 });

		~Font();

		SDL_Surface* GetSurface();


	private:
		void CreateSurface();

	private:
		std::string m_Text;
		TTF_Font* m_Font;
		int m_Size;
		SDL_Color m_Color;
		SDL_Color m_BackgroundColor;
		FontRender m_FontRender;
		SDL_Surface* m_Surface;
	};

}