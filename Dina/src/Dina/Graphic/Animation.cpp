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
		for (int i = 0; i < m_Spritesheet->GetNbSprites(); ++i)
			m_Sprites.push_back(m_Spritesheet->GetSprite(i));
	}
	Animation::Animation(Spritesheet* spriteSheet, std::vector<int> tileNumbers, double frameRate, bool invertDir) :
		m_Spritesheet(spriteSheet), m_FrameRate(frameRate), m_UsingSpritesheet(true), m_UsingInvertDir(invertDir)
	{
		for (int num : tileNumbers)
		{
			m_Sprites.push_back(m_Spritesheet->GetSprite(num));
		}
	}
	Animation::~Animation()
	{
		for (auto& anim : m_Animation)
		{
			delete anim;
			anim = nullptr;
		}
		m_Animation.clear();
		m_Sprites.clear();
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
				if (m_UsingInvertDir && (m_Frame <= 0 || m_Frame >= m_Sprites.size() - 1))
					m_Dir *= -1;
				else if (m_Frame >= m_Sprites.size())
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
			if (m_Frame >= 0 && m_Frame < m_Sprites.size() && m_Sprites[m_Frame])
				Graphic::DrawSprite(m_Sprites[m_Frame]);
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
	Point* Animation::GetOrigin()
	{
		if (m_UsingSpritesheet)
		{
			if (m_Frame >= 0 && m_Frame < m_Spritesheet->GetNbSprites() && m_Spritesheet->GetSprite(m_Frame))
			{
				return m_Spritesheet->GetSprite(m_Frame)->GetTexture()->GetOrigin();
			}
		}
		else
		{
			if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
			{
				return m_Animation[m_Frame]->GetOrigin();
			}
		}
		return nullptr;
	}
	void Animation::SetPosition(int x, int y)
	{
		if (m_UsingSpritesheet)
		{
			for(int i = 0; i < m_Spritesheet->GetNbSprites(); ++i)
				m_Spritesheet->GetSprite(i)->SetPosition(x, y);
		}
		else
		{
			for (auto& texture : m_Animation)
				texture->SetPosition(x, y);
		}
	}
	void Animation::SetDimensions(Quad dimensions)
	{
		if (m_UsingSpritesheet)
		{
			for (int i = 0; i < m_Spritesheet->GetNbSprites(); ++i)
				m_Spritesheet->GetSprite(i)->SetDimensions(dimensions);
		}
		else
		{
			for (auto& texture : m_Animation)
				texture->SetDimensions(dimensions);
		}
	}
	void Animation::SetRotation(double angle)
	{
		if (m_UsingSpritesheet)
		{
			for (int i = 0; i < m_Spritesheet->GetNbSprites(); ++i)
				m_Spritesheet->GetSprite(i)->GetTexture()->SetAngle(angle);
		}
		else
		{
			for (auto& texture : m_Animation)
				texture->SetAngle(angle);
		}
	}
	void Animation::SetOrigin(Point* point)
	{
		if (m_UsingSpritesheet)
		{
			for (int i = 0; i < m_Spritesheet->GetNbSprites(); ++i)
				m_Spritesheet->GetSprite(i)->GetTexture()->SetOrigin(point);
		}
		else
		{
			for (auto& texture : m_Animation)
				texture->SetOrigin(point);
		}
	}
}