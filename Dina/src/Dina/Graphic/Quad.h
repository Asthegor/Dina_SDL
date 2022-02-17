#pragma once

namespace Dina
{

	class DINA_API Quad
	{
	public:
		Quad(int x = 0, int y = 0, int width = 0, int height = 0);
		Quad(const SDL_Rect rect);
		Quad(const Quad& quad);

		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		SDL_Rect ToSDLRect();
	};

}