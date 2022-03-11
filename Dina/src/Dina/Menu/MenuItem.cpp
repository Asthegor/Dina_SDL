#include "dinapch.h"
#include "MenuItem.h"


namespace Dina
{
	MenuItem::MenuItem(const char* text, const char* fontName, int fontSize, SDL_Color color, SDL_Color selectedColor)
		: m_Text(text)
	{
		m_Font = new Font(text, fontName, fontSize, Dina::FontRender::Blended, color);
		DINA_CORE_ASSERT(m_Font != nullptr, "Unable to create Font object for surface.");

		m_SelectedFont = new Font(text, fontName, fontSize, Dina::FontRender::Blended, selectedColor);
		DINA_CORE_ASSERT(m_SelectedFont != nullptr, "Unable to create Font object for selected surface.");

		m_Dimensions = new Quad{ m_Font->GetSurface()->clip_rect};

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

	void MenuItem::SetAction(std::function<void()> action)
	{
		m_Action = action;
	}

	void MenuItem::SetOnHover(std::function<void()> hover)
	{
		m_Hover = hover;
	}

	void MenuItem::LaunchAction()
	{
		if (m_Action)
			m_Action();
	}

	void MenuItem::SetPosition(int x, int y)
	{
		m_Dimensions->x = x;
		m_Dimensions->y = y;
	}

	void MenuItem::SetSelected(bool selected)
	{
		m_Selected = selected;
	}

	bool MenuItem::IsSelected() const
	{
		return m_Selected;
	}

	void MenuItem::Update(double deltatime)
	{

	}

	void MenuItem::Draw()
	{

		if (m_Selected && m_SelectedFont)
			Graphic::DrawSurface(m_SelectedFont->GetSurface(), m_Dimensions->x, m_Dimensions->y);
		else if (m_Font)
			Graphic::DrawSurface(m_Font->GetSurface(), m_Dimensions->x, m_Dimensions->y);
	}
}