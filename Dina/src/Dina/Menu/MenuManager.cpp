#include "dinapch.h"
#include "MenuManager.h"
#include "Dina/Graphic/Graphic.h"
#include "Dina/Events/EventManager.h"
#include "Dina/Collisions/Collisions.h"

namespace Dina
{
	MenuManager::MenuManager()
	{

	}

	MenuManager::~MenuManager()
	{
		delete m_BackgroundTexture;
		delete m_TitleFont;
		delete m_TitleShadowFont;
		delete m_TitleTexture;
		delete m_TitleShadowTexture;

		items.clear();

		//EventDispatcher::Unsubscribe(this);
	}

	void MenuManager::SetBackground(const char* filePath)
	{
		m_BackgroundTexture = new Texture(Graphic::LoadTexture("Datas/Images/Menu/Background.png"));
	}

	void MenuManager::SetTitle(const char* title, const char* fontName, int fontSize, SDL_Color color, bool withShadow, int offset, SDL_Color shadowColor)
	{
		m_Title = title;
		m_WithShadow = withShadow;


		m_TitleFont = new Font(title, fontName, fontSize, Dina::FontRender::Blended, color);
		if (m_TitleFont)
		{
			m_TitleTexture = new Texture(Graphic::CreateTextureFromSurface(m_TitleFont->GetSurface()));

			if (m_TitleTexture)
			{
				// Calcul de la position du titre
				Quad* screen = Graphic::GetDimensions();
				Quad* titleRect = m_TitleTexture->GetDimensions();
				m_TitleTexture->SetPosition((screen->width - titleRect->width) / 2, screen->height / 8);

				if (withShadow)
				{
					m_TitleShadowFont = new Font(title, fontName, fontSize, Dina::FontRender::Blended, shadowColor);
					m_TitleShadowTexture = new Texture(Graphic::CreateTextureFromSurface(m_TitleShadowFont->GetSurface()));
					titleRect = m_TitleTexture->GetDimensions();
					m_TitleShadowTexture->SetPosition(titleRect->x + offset, titleRect->y + offset);
				}
			}
		}
	}
	void MenuManager::AddItem(const char* text, const char* fontName, int fontSize, std::function<void()> action, std::function<void()> hover, SDL_Color color, SDL_Color selectedColor)
	{
		MenuItem* item = new MenuItem { text, fontName, fontSize, color, selectedColor };
		item->SetAction(action);
		item->SetOnHover(hover);
		items.push_back(item);
	}

	void MenuManager::SetItemsStartHeight(int startHeight)
	{
		m_ItemsStartHeight = startHeight;

		SetItemsPositions();
	}

	void MenuManager::SetItemsPadding(int padding)
	{
		m_ItemsPadding = padding;

		SetItemsPositions();
	}

	void MenuManager::SetItemsPositions()
	{
		if (items.size() == 0)
			return;

		Quad* screen = Graphic::GetDimensions();

		int nextHeight = 0;
		for (int i = 0; i < items.size(); ++i)
		{
			Quad* itemDimension = items[i]->GetDimensions();
			itemDimension->x = (screen->width - itemDimension->width) / 2;
			itemDimension->y = i == 0 ? m_ItemsStartHeight : nextHeight;
			nextHeight = itemDimension->y + itemDimension->height + m_ItemsPadding;
		}
		delete screen;
	}


	void MenuManager::Update(double deltatime)
	{
		for (const auto& item : items)
		{
			item->Update(deltatime);
		}
	}

	void MenuManager::Draw()
	{
		if (m_BackgroundTexture)
			Graphic::DrawTexture(m_BackgroundTexture);

		// Title
		if (m_TitleTexture)
		{
			if (m_WithShadow && m_TitleShadowTexture)
				Graphic::DrawTexture(m_TitleShadowTexture);

			Graphic::DrawTexture(m_TitleTexture);
		}

		// Items
		for (auto& item : items)
		{
			item->Draw();
		}
	}


	// Keyboard events
	void MenuManager::OnKeyPressed(KeyCode key)
	{
		if (key == KeyCode::Down)
		{
			if (m_CurrentSelectedItem >= 0)
				items[m_CurrentSelectedItem]->SetSelected(false);
			m_CurrentSelectedItem = ++m_CurrentSelectedItem >= items.size() ? 0 : m_CurrentSelectedItem;
			items[m_CurrentSelectedItem]->SetSelected(true);
		}
		else if (key == KeyCode::Up)
		{
			if (m_CurrentSelectedItem >= 0)
				items[m_CurrentSelectedItem]->SetSelected(false);
			m_CurrentSelectedItem = --m_CurrentSelectedItem < 0 ? static_cast<int>(items.size() - 1) : m_CurrentSelectedItem;
			items[m_CurrentSelectedItem]->SetSelected(true);
		}
	}


	// Mouse events
	void MenuManager::OnMouseMove(int x, int y)
	{
		for (const auto& item : items)
		{
			if (Collisions::Collide({ x, y }, *item->GetDimensions()))
			{
				item->SetSelected(true);
				if (m_CurrentSelectedItem < 0 || items[m_CurrentSelectedItem] != item)
				{
					for (int i = 0; i < items.size(); ++i)
					{
						if (items[i] == item)
						{
							m_CurrentSelectedItem = i;
							break;
						}
					}
				}
			}
			else
				item->SetSelected(false);
		}
	}
	void MenuManager::OnMousePressed(int button, int x, int y, int clicks)
	{
		if (button == 1)
		{
			for (const auto& item : items)
			{
				if (items.size() == 0)
					break;

				if (Collisions::Collide({ x, y }, *item->GetDimensions()))
				{
					item->LaunchAction();
				}
			}
		}
	}

}