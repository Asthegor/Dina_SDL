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
		void SetSelectedPosition(int x, int y);
		void SetSelected(bool selected = false);

		void CenterOnY(int y, int minWidth, int maxWidth);
		void CenterOnX(int x, int minHeight, int maxHeight);

		bool IsSelected() const;
		std::string GetText() const;

		void SetAction(std::function<void(MenuItem*)> action);
		void SetOnHover(std::function<void(MenuItem* menuItem, bool state)> hover);
		void LaunchAction();
		void LaunchHover(bool state);

		void SetFont(const char* fontName, int fontSize);
		Font* GetFont();
		
		void SetSelectedFont(const char* fontName, int fontSize);
		Font* GetSelectedFont();

		void SetColor(SDL_Color color);
		SDL_Color GetColor();

		void SetSelectedColor(SDL_Color selectedColor);
		SDL_Color GetSelectedColor();

		void Update(double deltatime);
		void Draw();

	private:
		std::function<void(MenuItem* menuItem)> m_Action = nullptr;
		std::function<void(MenuItem* menuItem, bool state)> m_Hover = nullptr;
		bool m_Selected = false;
		std::string m_Text;
		std::string m_FontName;
		int m_FontSize;
		
		Font* m_Font = nullptr;
		Font* m_SelectedFont = nullptr;
		Quad* m_Dimensions = nullptr;
		Quad* m_SelectedDimensions = nullptr;
		SDL_Color m_Color;
		SDL_Color m_SelectedColor;
	};

	

}