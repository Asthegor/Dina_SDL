#include "dinapch.h"
#include "Animation.h"
#include "Spritesheet.h"

namespace Dina
{
	Animation::Animation(const char* fileName, const char* extWithDot, int nbImages, double frameRate) :
		m_FrameRate(frameRate), m_UsingSpritesheet(false)
	{
		Texture* texture = nullptr;
		for (int i = 0; i < nbImages; ++i)
		{
			std::string file { fileName };
			file += std::to_string(i);
			file += extWithDot;
			texture = new Texture(file.c_str());
			if (texture)
				m_Animation.push_back(texture);
		}

	}

	Animation::Animation(const char* fileName, int tileWidth, int tileHeight, double frameRate, bool invertDir) :
		m_FrameRate(frameRate), m_UsingSpritesheet(true), m_UsingInvertDir(invertDir)
	{
		m_Spritesheet = new Spritesheet { fileName, tileWidth, tileHeight };
	}

	Animation::~Animation()
	{
		for (auto& anim : m_Animation)
		{
			delete anim;
			anim = nullptr;
		}
		m_Animation.clear();
		delete m_Spritesheet;
	}
	void Animation::Load()
	{}
	void Animation::Update(double deltatime)
	{
		m_Timer += deltatime;
		if (m_Timer > m_FrameRate)
		{
			m_Timer = 0.0;
			m_Frame += 1 * m_Dir;

			if (m_UsingSpritesheet)
			{
				if (m_UsingInvertDir && (m_Frame <= 0 || m_Frame >= m_Spritesheet->GetNbSprites() - 1))
					m_Dir *= -1;
				else if (m_Frame >= m_Spritesheet->GetNbSprites())
					m_Frame = 0;
			}
			else if (m_Frame >= m_Animation.size())
				m_Frame = 0;
		}
	}
	void Animation::Draw()
	{
		if (m_UsingSpritesheet)
		{
			if (m_Frame >= 0 && m_Frame < m_Spritesheet->GetNbSprites() && m_Spritesheet->GetSprite(m_Frame))
				Graphic::DrawSprite(m_Spritesheet->GetSprite(m_Frame));
		}
		else
		{
			if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
				Graphic::DrawTexture(m_Animation[m_Frame]);
		}
	}
	Quad* Animation::GetDimensions()
	{
		if (m_UsingSpritesheet)
		{
			if (m_Frame >= 0 && m_Frame < m_Spritesheet->GetNbSprites() && m_Spritesheet->GetSprite(m_Frame))
			{
				return m_Spritesheet->GetSprite(m_Frame)->GetDimensions();
			}
		}
		else
		{
			if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
			{
				return m_Animation[m_Frame]->GetDimensions();
			}
		}
		return nullptr;
	}
	void Animation::SetPosition(int x, int y)
	{
		if (m_UsingSpritesheet)
		{
			if (m_Frame >= 0 && m_Frame < m_Spritesheet->GetNbSprites() && m_Spritesheet->GetSprite(m_Frame))
			{
				m_Spritesheet->GetSprite(m_Frame)->SetPosition(x, y);
			}
		}
		else
		{
			if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
			{
				m_Animation[m_Frame]->SetPosition(x, y);
			}
		}
	}
	void Animation::SetDimensions(Quad dimensions)
	{

		if (m_UsingSpritesheet)
		{
			if (m_Frame >= 0 && m_Frame < m_Spritesheet->GetNbSprites() && m_Spritesheet->GetSprite(m_Frame))
			{
				m_Spritesheet->GetSprite(m_Frame)->SetDimensions(dimensions);
			}
		}
		else
		{
			if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
			{
				m_Animation[m_Frame]->SetDimensions(dimensions);
			}
		}
	}
}