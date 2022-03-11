#pragma once
#include <string>
#include <SDL.h>

namespace Dina
{
	class DINA_API DinaGame
	{
	public:
		DinaGame();
		~DinaGame();

		void SetTitle(const std::string title);
		void SetDimensions(int width, int height);
		void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);

		void Run();

		virtual void Load() = 0;
		virtual void Update(double deltatime) = 0;
		virtual void Draw() = 0;

	private:
		std::string m_Title;
		int m_Width = 1280;
		int m_Height = 800;
		bool m_Quit = false;

		const double m_MaxDeltatime = 1.0 / 60.0;

		SDL_Color m_BackgroundColor;

	private:
		void Init();
	};


	DinaGame* CreateGame();

}