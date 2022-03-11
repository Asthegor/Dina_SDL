#pragma once
#include "Dina/Graphic/Graphic.h"
#include "Dina/Graphic/Font.h"
#include "Dina/Graphic/Quad.h"
#include <functional>

namespace Dina

{
	class DINA_API MenuItem
	{
	public:
		MenuItem(const char* text, const char* fontName, int fontSize, SDL_Color color, SDL_Color selectedColor);
		~MenuItem();

		Quad* GetDimensions() const;

		void SetPosition(int x, int y);
		void SetSelected(bool selected = false);

		bool IsSelected() const;
		std::string GetText() const;

		void SetAction(std::function<void()> action);
		void SetOnHover(std::function<void()> hover);
		void LaunchAction();


		void Update(double deltatime);
		void Draw();

	private:
		std::function<void()> m_Action = nullptr;
		std::function<void()> m_Hover = nullptr;
		bool m_Selected = false;
		std::string m_Text;
		
		Font* m_Font = nullptr;
		Font* m_SelectedFont = nullptr;
		Quad* m_Dimensions = nullptr;
	};

}