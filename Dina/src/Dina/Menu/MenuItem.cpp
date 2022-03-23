#include "dinapch.h"
#include "MenuItem.h"


namespace Dina
{
	MenuItem::MenuItem(const char* text, const char* fontName, int fontSize, SDL_Color color, SDL_Color selectedColor)
		: m_Text(text), m_FontName(fontName), m_FontSize(fontSize), m_Color(color), m_SelectedColor(selectedColor)
	{
		m_Font = new Font(m_Text.c_str(), m_FontName.c_str(), m_FontSize, Dina::FontRender::Blended, m_Color);
		if (!m_Font)
			DINA_CORE_ERROR("Unable to create Font object for surface.");

		m_SelectedFont = new Font(m_Text.c_str(), m_FontName.c_str(), m_FontSize, Dina::FontRender::Blended, m_SelectedColor);
		if (!m_SelectedFont)
			DINA_CORE_ERROR("Unable to create Font object for selected surface.");

		m_Dimensions = new Quad { m_Font->GetSurface()->clip_rect };
		m_SelectedDimensions = new Quad { m_SelectedFont->GetSurface()->clip_rect };
	}

	MenuItem::~MenuItem()
	{
		delete m_Font;
		delete m_SelectedFont;
		delete m_Dimensions;
	}

	Quad* MenuItem::GetDimensions() const
	{
		return m_Dimensions;
	}

	std::string MenuItem::GetText() const
	{
		return m_Text;
	}

	void MenuItem::SetAction(std::function<void(MenuItem*)> action)
	{
		m_Action = action;
	}

	void MenuItem::SetOnHover(std::function<void(MenuItem* menuItem, bool state)> hover)
	{
		m_Hover = hover;
	}

	void MenuItem::LaunchAction()
	{
		if (m_Action)
			m_Action(this);
	}
	void MenuItem::LaunchHover(bool state)
	{
		if (m_Hover)
			m_Hover(this, state);
	}
	void MenuItem::SetFont(const char* fontName, int fontSize)
	{
		Font* font = new Font(GetText().c_str(), fontName, fontSize, Dina::FontRender::Blended, m_Color);
		if (font)
		{
			delete m_Font;
			m_Font = font;
			m_Dimensions = new Quad { m_Font->GetSurface()->clip_rect };
		}
	}
	Font* MenuItem::GetFont()
	{
		return m_Font;
	}
	Font* MenuItem::GetSelectedFont()
	{
		return m_SelectedFont;
	}
	void MenuItem::SetSelectedFont(const char* fontName, int fontSize)
	{
		Font* font = new Font(GetText().c_str(), fontName, fontSize, Dina::FontRender::Blended, m_SelectedColor);
		if (font)
		{
			delete m_SelectedFont;
			m_SelectedFont = font;
			m_SelectedDimensions = new Quad { m_SelectedFont->GetSurface()->clip_rect };
		}
	}
	void MenuItem::SetPosition(int x, int y)
	{
		m_Dimensions->x = x;
		m_Dimensions->y = y;
	}

	void MenuItem::SetSelectedPosition(int x, int y)
	{
		m_SelectedDimensions->x = x;
		m_SelectedDimensions->y = y;
	}

	void MenuItem::SetSelected(bool selected)
	{
		m_Selected = selected;
	}

	void MenuItem::CenterOnY(int y, int minWidth, int maxWidth)
	{
		int x = (maxWidth - m_Dimensions->width) / 2 + minWidth;
		SetPosition(x, y);
		x = (maxWidth - m_SelectedDimensions->width) / 2 + minWidth;
		SetSelectedPosition(x, y);
	}

	void MenuItem::CenterOnX(int x, int minHeight, int maxHeight)
	{
		int y = (maxHeight - m_Dimensions->height) / 2 + minHeight;
		SetPosition(x, y);
		y = (maxHeight - m_SelectedDimensions->height) / 2 + minHeight;
		SetSelectedPosition(x, y);
	}

	bool MenuItem::IsSelected() const
	{
		return m_Selected;
	}

	void MenuItem::SetColor(SDL_Color color)
	{

		Font* font = new Font(m_Text.c_str(), m_FontName.c_str(), m_FontSize, Dina::FontRender::Blended, color);
		if (font)
		{
			delete m_Font;
			m_Font = font;
		}
	}

	SDL_Color MenuItem::GetColor()
	{
		return m_Color;
	}

	void MenuItem::SetSelectedColor(SDL_Color selectedColor)
	{
		Font* font = new Font(m_Text.c_str(), m_FontName.c_str(), m_FontSize, Dina::FontRender::Blended, selectedColor);
		if (font)
		{
			delete m_SelectedFont;
			m_SelectedFont = font;
		}
	}

	SDL_Color MenuItem::GetSelectedColor()
	{
		return m_SelectedColor;
	}

	void MenuItem::Update(double deltatime)
	{
	}

	void MenuItem::Draw()
	{

		if (m_Selected && m_SelectedFont)
			Graphic::DrawSurface(m_SelectedFont->GetSurface(), m_SelectedDimensions->x, m_SelectedDimensions->y);
		else if (m_Font)
			Graphic::DrawSurface(m_Font->GetSurface(), m_Dimensions->x, m_Dimensions->y);
	}
}