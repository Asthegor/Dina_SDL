#include "dinapch.h"
#include "Animation.h"

namespace Dina
{
    Animation::Animation(const char* fileName, const char* extWithDot, int nbImages, double frameRate) :
        m_FrameRate(frameRate)
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
    Animation::~Animation()
    {
        for (auto& anim : m_Animation)
        {
            delete anim;
            anim = nullptr;
        }
        m_Animation.clear();
    }
    void Animation::Load()
    {}
    void Animation::Update(double deltatime)
    {
        m_Timer += deltatime;
        if (m_Timer > m_FrameRate)
        {
            m_Timer = 0.0;
            ++m_Frame;
            if (m_Frame >= m_Animation.size())
                m_Frame = 0;
        }
    }
    void Animation::Draw()
    {
        if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
            Graphic::DrawTexture(m_Animation[m_Frame]);
    }
    Quad* Animation::GetDimensions()
    {
        if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
        {
            return m_Animation[m_Frame]->GetDimensions();
        }
        return nullptr;
    }
    void Animation::SetPosition(int x, int y)
    {
        if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
        {
            m_Animation[m_Frame]->SetPosition(x, y);
        }
    }
    void Animation::SetDimensions(Quad dimensions)
    {
        if (m_Frame >= 0 && m_Frame < m_Animation.size() && m_Animation[m_Frame])
        {
            m_Animation[m_Frame]->SetDimensions(dimensions);
        }
    }
}