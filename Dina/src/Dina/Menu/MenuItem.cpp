#include "dinapch.h"
#include "MenuItem.h"

#include "Dina/Graphic/Graphic.h"

namespace Dina
{
	MenuItem::MenuItem(const char* text, const char* fontName, int fontSize, SDL_Color color, SDL_Color selectedColor)
		: m_Text(text)
	{
		Font* font = new Font(text, fontName, fontSize, Dina::FontRender::Blended, color);
		DINA_CORE_ASSERT(font != nullptr, "Unable to create Font object for surface.");
		m_Surface = font->GetSurface();
		delete font;

		font = new Font(text, fontName, fontSize, Dina::FontRender::Blended, selectedColor);
		DINA_CORE_ASSERT(font != nullptr, "Unable to create Font object for selected surface.");
		m_SelectedSurface = font->GetSurface();
		delete font;

		m_Dimensions = new Quad{ m_Surface->clip_rect };

	}

	MenuItem::~MenuItem()
	{
		SDL_FreeSurface(m_Surface);
		SDL_FreeSurface(m_SelectedSurface);

		//delete m_Dimensions;
		m_Dimensions = nullptr;

		//delete m_Action;
		m_Action = nullptr;
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

		if (m_Selected && m_SelectedSurface)
			Graphic::DrawSurface(m_SelectedSurface, m_Dimensions->x, m_Dimensions->y);
		else if (m_Surface)
			Graphic::DrawSurface(m_Surface, m_Dimensions->x, m_Dimensions->y);
	}
}