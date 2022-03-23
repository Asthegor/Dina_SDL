#include "dinapch.h"
#include "MenuManager.h"
#include "Dina/Graphic/Graphic.h"
#include "Dina/Events/EventManager.h"
#include "Dina/Utils/Collisions.h"

namespace Dina
{
	MenuManager::MenuManager()
	{

	}

	MenuManager::~MenuManager()
	{
		delete m_BackgroundTexture;
		m_Titles.clear();
		items.clear();
	}

	void MenuManager::SetBackground(const char* filePath)
	{
		m_BackgroundTexture = new Texture(Graphic::LoadTexture("Datas/Images/Menu/Background.png"));
	}

	void MenuManager::AddTitle(const char* title, int posY, const char* fontName, int fontSize, SDL_Color color, bool withShadow, int offset, SDL_Color shadowColor)
	{
		MenuTitle* menutitle = new MenuTitle(title, posY, fontName, fontSize, color, withShadow, offset, shadowColor);
		m_Titles.push_back(menutitle);
	}
	void MenuManager::AddItem(const char* text, const char* fontName, int fontSize, std::function<void(MenuItem*)> action, std::function<void(MenuItem*,bool)> hover, SDL_Color color, SDL_Color selectedColor)
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
			int y = i == 0 ? m_ItemsStartHeight : nextHeight;
			items[i]->CenterOnY(y, 0, screen->width);
			nextHeight = y + itemDimension->height + m_ItemsPadding;
		}
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
		for (auto& title : m_Titles)
		{
			title->Draw();
		}

		// Items
		for (auto& item : items)
		{
			item->Draw();
		}
	}


	// Keyboard events
	void MenuManager::OnKeyReleased(KeyCode key)
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
				item->LaunchHover(true);
			}
			else
			{
				item->SetSelected(false);
				item->LaunchHover(false);
			}
		}
		SetItemsPositions();
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