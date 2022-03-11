#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Quad.h"
#include "Sprite.h"

namespace Dina
{
	class DINA_API Graphic
	{
	public:
		enum class ShapeMode { Fill = 1, Line};
		static void Init(int width, int height, const char* title = "Dina");


		static Quad* GetDimensions();

		static void ShowCursor(bool show);

		static void SetBackgroundColor(SDL_Color backgroundColor);

		//Loading
		static SDL_Texture* LoadTexture(const char* filePath);
		static void* LoadVoidTexture(const char* filePath);

		//Conversions
		static SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface);

		//Drawing
		static void DrawTexture(Texture* texture, SDL_Color color = {255,255,255,255});
		static void DrawSurface(SDL_Surface* surface, int x = 0, int y = 0);
		static void DrawSprite(Sprite* sprite);
		static void DrawPolyline(double** points, double x, double y, int pointsc, SDL_Color color = {255,255,255,255});
		static void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color = { 255,255,255,255 });
		static void DrawRectangle(Quad quad);

		static void DrawPointOnSurface(SDL_Surface* surface, Point point, SDL_Color color = { 255,255,255,255 });
		static void DrawCircleOnSurface(SDL_Surface* surface, Point point, int radius, ShapeMode shapeMode = ShapeMode::Line, SDL_Color color = { 255,255,255,255 });

		static void Clear();
		static void Render();
		static void Quit();

	private:
		static Graphic* GetInstance();
		static void DestroyInstance();
		static Graphic* m_Instance;
		static Quad* m_ScreenDimensions;
		SDL_Renderer* m_Renderer;
		SDL_Window* m_Window;
		~Graphic();
	};


}