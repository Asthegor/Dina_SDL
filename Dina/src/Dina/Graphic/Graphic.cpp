#include "dinapch.h"

#include "Graphic.h"
#include "Texture.h"
#include <SDL_image.h>

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
		return SDL_CreateTextureFromSurface(GetInstance()->m_Renderer, surface);
	}

	SDL_Texture* Graphic::LoadTexture(const char* filePath)
	{
		SDL_Texture* texture = nullptr;

		texture = IMG_LoadTexture(GetInstance()->m_Renderer, filePath);
		if (!texture) {
			DINA_CORE_ERROR("Unable to load image \"{0}\". Error: {1}", filePath, SDL_GetError());
			return nullptr;
		}

		return texture;
	}

	void Graphic::DrawTexture(Texture* texture)
	{
		if (texture)
		{
			Dina::Quad* quad = texture->GetDimensions();
			SDL_Rect rect = quad->ToSDLRect();
			SDL_RenderCopy(GetInstance()->m_Renderer, texture->GetTexture(), nullptr, &rect);
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
		SDL_RenderCopy(GetInstance()->m_Renderer, sprite->GetTexture()->GetTexture(), &rectImg, &rectPos);
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