#include "dinapch.h"
#include "DinaGame.h"
#include "Dina/Scene/GameState.h"
#include "Dina/Utils/GameTime.h"
#include "Dina/Graphic/Graphic.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Dina/Events/EventManager.h"

namespace Dina
{
	DinaGame::DinaGame() :
		m_BackgroundColor { 0,0,0,0 }
	{
		Init();
	}

	DinaGame::~DinaGame()
	{
		GameState::Quit();
		Graphic::Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void DinaGame::SetTitle(const std::string title)
	{
		m_Title = title;
	}

	void DinaGame::SetDimensions(int width, int height)
	{
		m_Width = width;
		m_Height = height;
	}

	void DinaGame::SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		m_BackgroundColor = { red, green, blue, alpha };
	}

	void DinaGame::Run()
	{

		Graphic::Init(m_Width, m_Height, m_Title.c_str());
		DINA_CORE_TRACE("Window and renderer successfully created.");

		DINA_CORE_TRACE("Add window title.");

		//SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SystemCursor::SDL_SYSTEM_CURSOR_ARROW);
		SDL_SetCursor(cursor);

		// Chargement des images
		DINA_CORE_TRACE("Loading game datas.");
		Load();

		double deltatime = 0.0;
		double maxDeltatime = 1.0 / 60.0;
		// Boucle de jeu
		while (!m_Quit)
		{

			deltatime = GameTime::GetElapsedTime();

			m_Quit = Dina::EventManager::Execute();

			Graphic::SetBackgroundColor(m_BackgroundColor);

			if (deltatime < maxDeltatime)
			{
				double delay = maxDeltatime - deltatime;
				deltatime = std::max(deltatime, maxDeltatime);
				SDL_Delay(static_cast<Uint32>(delay * 1000));
			}
			Update(deltatime);

			Graphic::Clear();
			Draw();
			Graphic::Render();
		}
		SDL_FreeCursor(cursor);
	}

	void DinaGame::Init()
	{
		SDL_SetMainReady();
		int success = 0;

		success = SDL_Init(SDL_INIT_EVERYTHING);
		DINA_CORE_ASSERT((success == 0), "Unable to initialize SDL2. Error: {0}", SDL_GetError());
		DINA_CORE_TRACE("SDL initialization successful.");

		// Initialize SDL_Image
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		success = IMG_Init(imgFlags) & imgFlags;
		DINA_CORE_ASSERT(success > 0, "Unable to initialize SDL_image. Error: {0}", IMG_GetError());
		DINA_CORE_TRACE("SDL_image initialization successful.");


		// Initialize SDL_ttf
		success = TTF_Init();
		DINA_CORE_ASSERT(success == 0, "Unable to initialize SDL_ttf. Error: {0}", TTF_GetError());
		DINA_CORE_TRACE("SDL_ttf initialization successful.");

	}
}