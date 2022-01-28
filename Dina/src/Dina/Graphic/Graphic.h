#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Quad.h"


namespace Dina
{
	class DINA_API Graphic
	{
	public:
		static void Init(int width, int height, const char* title = "Dina");


		static Quad* GetDimensions();

		static void ShowCursor(bool show);

		static void SetBackgroundColor(SDL_Color backgroundColor);

		//Loading
		static SDL_Texture* LoadTexture(const char* filePath);

		//Conversions
		static SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

		//Drawing
		static void DrawTexture(Texture* texture);
		static void DrawSurface(SDL_Surface* surface, int x = 0, int y = 0);


		static void Clear();
		static void Render();
		static void Quit();

	private:
		static Graphic* GetInstance();
		static void DestroyInstance();
		static Graphic* m_Instance;
		SDL_Renderer* m_Renderer;
		SDL_Window* m_Window;
		~Graphic();
	};


}