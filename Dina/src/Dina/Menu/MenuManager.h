#pragma once
#include <SDL.h>
#include <vector>
#include "MenuItem.h"
#include "Dina/Graphic/Texture.h"
#include "Dina/Graphic/Font.h"
#include <functional>

namespace Dina
{

	class DINA_API MenuManager : public Event
	{
	public:
		MenuManager();
		~MenuManager();

		void SetBackground(const char* filePath);
		void SetTitle(const char* title, const char* fontName, int fontSize, SDL_Color color = { 255,255,255,255 }, 
					  bool withShadow = false, int offset = 0, SDL_Color shadowColor = { 100,100,100,255 });

		void AddItem(const char* text, const char* fontName, int fontSize, 
					 std::function<void()> action = nullptr, std::function<void()> hover = nullptr, 
					 SDL_Color color = { 255,255,255,255 }, SDL_Color selectedColor = { 255,255,255,255 });

		void SetItemsStartHeight(int startHeight);
		void SetItemsPadding(int padding = 10);

	private:
		void SetItemsPositions();

	public:

		void Update(double deltatime);
		void Draw();

		// Surcharge des fonctions de Event
		virtual void OnKeyPressed(KeyCode key) override;
		virtual void OnMouseMove(int x, int y) override;
		virtual void OnMousePressed(int button, int x, int y, int clicks) override;


	private:
		const char* m_Title = nullptr;
		bool m_WithShadow = false;
		int m_ItemsStartHeight = 0;
		int m_ItemsPadding = 0;

		std::vector<MenuItem*> items;
		int m_CurrentSelectedItem = -1;

		Texture* m_BackgroundTexture = nullptr;
		Font* m_TitleFont = nullptr;
		Font* m_TitleShadowFont = nullptr;
		Texture* m_TitleTexture = nullptr;
		Texture* m_TitleShadowTexture = nullptr;

	};

}