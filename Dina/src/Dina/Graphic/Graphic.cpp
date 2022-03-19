#include "dinapch.h"

#include "Graphic.h"

namespace Dina
{
	void Graphic::Init(int width, int height, const char* title)
	{

		int result = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &GetInstance()->m_Window, &GetInstance()->m_Renderer);
		DINA_CORE_ASSERT(result == 0, "Unable to create window and/or renderer. Error:{0}.", SDL_GetError());

		SDL_SetWindowTitle(GetInstance()->m_Window, title);
	}

	void Graphic::Clear()
	{
		int success = SDL_RenderClear(GetInstance()->m_Renderer);
		if (success != 0)
		{
			DINA_CORE_ERROR("Unable to clear the renderer. Error: {0}", SDL_GetError());
			return;
		}
	}

	void Graphic::Render()
	{
		if (GetInstance()->m_Renderer)
			SDL_RenderPresent(GetInstance()->m_Renderer);
		else
			DINA_CORE_ERROR("Unable to retreive the renderer.");
	}

	void Graphic::SetBackgroundColor(SDL_Color backgroundColor)
	{
		int success = SDL_SetRenderDrawColor(GetInstance()->m_Renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		if (success != 0)
		{
			DINA_CORE_ERROR("Unable to draw the background color [{0},{1},{2},{3}]. Error: {4}", backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a, SDL_GetError());
			return;
		}
	}

	Quad* Graphic::GetDimensions()
	{
		if (!m_ScreenDimensions)
		{
			int width;
			int height;
			int result = SDL_GetRendererOutputSize(GetInstance()->m_Renderer, &width, &height);

			if (result != 0)
			{
				DINA_CORE_ERROR("Unable to retreive the rendering dimensions. Error: {0}", SDL_GetError());
				return nullptr;
			}
			m_ScreenDimensions = new Quad { 0, 0, width, height };
		}
		return m_ScreenDimensions;
	}

	void Graphic::ShowCursor(bool show)
	{
		if (show)
		{
			if (SDL_ShowCursor(SDL_QUERY) == SDL_DISABLE)
				SDL_ShowCursor(SDL_ENABLE);
		}
		else
			SDL_ShowCursor(SDL_DISABLE);
		SDL_SetCursor(NULL);
	}

	SDL_Texture* Graphic::CreateTextureFromSurface(SDL_Surface* surface)
	{
		if (surface)
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(GetInstance()->m_Renderer, surface);
			if (!texture)
				DINA_CORE_ERROR("Unable to create texture. Error: {0}", SDL_GetError());

			return texture;
		}
		return nullptr;
	}

	SDL_Texture* Graphic::CreateTexture(int width, int height)
	{
		return SDL_CreateTexture(GetInstance()->m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	}

	SDL_Texture* Graphic::LoadTexture(const char* filePath)
	{
		SDL_Texture* texture = nullptr;

		texture = IMG_LoadTexture(GetInstance()->m_Renderer, filePath);
		if (!texture)
		{
			DINA_CORE_ERROR("Unable to load image \"{0}\". Error: {1}", filePath, SDL_GetError());
			return nullptr;
		}
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

		return texture;
	}

	void* Graphic::LoadVoidTexture(const char* filePath)
	{
		return reinterpret_cast<void*>(LoadTexture(filePath));
	}

	void Graphic::DrawTexture(Texture* texture, SDL_Color color)
	{
		if (texture)
		{
			Dina::Quad* quad = texture->GetDimensions();
			SDL_Rect rect = quad->ToSDLRect();
			SDL_Texture* sdlTexture = texture->GetTexture();
			int success = SDL_SetTextureColorMod(sdlTexture, color.r, color.g, color.b);
			DINA_CORE_ASSERT((success == 0), "Unable to color the given texture - Error: {0}", SDL_GetError());
			success = SDL_SetTextureAlphaMod(sdlTexture, color.a);
			DINA_CORE_ASSERT((success == 0), "Unable to alpha color the given texture - Error: {0}", SDL_GetError());
			success = SDL_RenderCopyEx(GetInstance()->m_Renderer, sdlTexture, nullptr, &rect, texture->GetAngle(), (SDL_Point*) texture->GetOrigin(), texture->GetFlip());
			DINA_CORE_ASSERT((success == 0), "Unable to draw the given texture - Error: {0}", SDL_GetError());
		}
	}

	void Graphic::DrawSurface(SDL_Surface* surface, int x, int y)
	{
		Texture* texture = new Texture(Graphic::CreateTextureFromSurface(surface), x, y);
		DrawTexture(texture);
		delete texture;
	}

	void Graphic::DrawSprite(Sprite* sprite)
	{
		SDL_Rect rectPos = sprite->GetDimensions()->ToSDLRect();
		SDL_Rect rectImg = sprite->GetImgPosInSheet()->ToSDLRect();
		Texture* texture = sprite->GetTexture();
		SDL_RenderCopyEx(GetInstance()->m_Renderer,
						 texture->GetTexture(), &rectImg, &rectPos,
						 texture->GetAngle(), (SDL_Point*) texture->GetOrigin(), texture->GetFlip());
	}

	void Graphic::DrawPolyline(double** points, double x, double y, int pointsc, SDL_Color color)
	{
		for (int i = 1; i < pointsc; ++i)
		{
			DrawLine(static_cast<int>(x + points[i - 1][0]), static_cast<int>(y + points[i - 1][1]), static_cast<int>(x + points[i][0]), static_cast<int>(y + points[i][1]));
		}
	}

	void Graphic::DrawLine(int x1, int y1, int x2, int y2, SDL_Color color)
	{
		SDL_SetRenderDrawColor(GetInstance()->m_Renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(GetInstance()->m_Renderer, x1, y1, x2, y2);
	}

	void Graphic::DrawRectangle(Quad quad)
	{

		SDL_Rect rect = quad.ToSDLRect();
		SDL_RenderDrawRect(GetInstance()->m_Renderer, &rect);
	}

	void Graphic::DrawPointOnSurface(SDL_Surface* surface, Point point, SDL_Color color)
	{
		Uint32* const target_pixel = (Uint32*) ((Uint8*) surface->pixels
												+ point.y * surface->pitch
												+ point.x * surface->format->BytesPerPixel);
		Uint32 pixel =
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
		(color.a << 24) | (color.b << 16) | (color.g << 8) | color.r;
#else
			(color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
#endif
		* target_pixel = pixel;
	}

	void Graphic::DrawCircleOnSurface(SDL_Surface* surface, Point point, int radius, ShapeMode shapeMode, SDL_Color color)
	{
		const int32_t diameter = (radius * 2);

		if (shapeMode == ShapeMode::Line)
		{
			int32_t x = (radius - 1);
			int32_t y = 0;
			int32_t tx = 1;
			int32_t ty = 1;
			int32_t error = (tx - diameter);




			while (x >= y)
			{
				//  Each of the following renders an octant of the circle
				DrawPointOnSurface(surface, { point.x + x, point.y - y }, color);
				DrawPointOnSurface(surface, { point.x + x, point.y + y }, color);
				DrawPointOnSurface(surface, { point.x - x, point.y - y }, color);
				DrawPointOnSurface(surface, { point.x - x, point.y + y }, color);
				DrawPointOnSurface(surface, { point.x + y, point.y - x }, color);
				DrawPointOnSurface(surface, { point.x + y, point.y + x }, color);
				DrawPointOnSurface(surface, { point.x - y, point.y - x }, color);
				DrawPointOnSurface(surface, { point.x - y, point.y + x }, color);

				if (error <= 0)
				{
					++y;
					error += ty;
					ty += 2;
				}

				if (error > 0)
				{
					--x;
					tx += 2;
					error += (tx - diameter);
				}
			}
		}
		else if (shapeMode == ShapeMode::Fill)
		{
			/*
			procédure tracerSegment(entier x1, entier y1, entier x2, entier y2) est
				déclarer entier x, y, dx, dy;
				déclarer entier e; // valeur d’erreur
				déclarer entier e(1, 0), e(0, 1);  // incréments
				dy ← y2 - y1;
				dx ← x2 - x1;
				y ← y1;  // rangée initiale
				e ← - dx;  // valeur d’erreur initiale
				e(1, 0) ←  dy × 2;
				e(0, 1) ← - dx × 2;
				pour x variant de x1 jusqu’à x2 par incrément  de 1 faire
					tracerPixel(x, y);
				si(e ← e + e(1, 0)) ≥ 0 alors  // erreur pour le pixel suivant de même rangée
					y ← y + 1;  // choisir plutôt le pixel suivant dans la rangée supérieure
				e ← e + e(0, 1);  // ajuste l’erreur commise dans cette nouvelle rangée
				fin si;
				fin pour;
			fin procédure;
			*/
		}
	}

	void Graphic::Quit()
	{
		DestroyInstance();
	}

	Graphic::~Graphic()
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;

		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

	Graphic* Graphic::m_Instance = nullptr;
	Quad* Graphic::m_ScreenDimensions = nullptr;

	Graphic* Graphic::GetInstance()
	{
		if (!m_Instance)
			m_Instance = new Graphic;

		return m_Instance;
	}

	void Graphic::DestroyInstance()
	{
		delete m_Instance;
		m_Instance = nullptr;
	}

}