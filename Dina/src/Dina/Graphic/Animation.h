#pragma once
#include "Dina/Core/Component.h"
#include "Texture.h"
#include "Quad.h"

namespace Dina
{
    class DINA_API Animation : public Component
    {
    public:
        Animation(const char* fileName, const char* extWithDot, int nbImages, double frameRate);
        virtual ~Animation();

        void Load();
        void Update(double deltatime);
        void Draw();

        Quad* GetDimensions();
        void SetPosition(int x, int y);
        void SetDimensions(Quad dimensions);

    private:
        std::vector<Texture*> m_Animation;
        int m_Frame = 0;
        double m_FrameRate = 0.0;
        double m_Timer = 0.0;
    };

}