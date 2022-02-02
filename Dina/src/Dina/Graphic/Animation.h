#pragma once
#include "Dina/Core/Component.h"
#include "Texture.h"
#include "Quad.h"


namespace Dina
{
    class DINA_API Spritesheet;

    class DINA_API Animation : public Component
    {
    public:
        Animation(const char* fileName, const char* extWithDot, int nbImages, double frameRate);
        Animation(const char* fileName, int tileWidth, int tileHeight, double frameRate, bool invertDir = false);
        Animation(Spritesheet* spriteSheet, std::vector<int> tileNumbers, double frameRate, bool invertDir = false);
        virtual ~Animation();

        void Load();
        void Update(double deltatime);
        void Draw();

        Quad* GetDimensions();
        void SetPosition(int x, int y);
        void SetDimensions(Quad dimensions);

    private:
        std::vector<Texture*> m_Animation;
        std::vector<Sprite*> m_Sprites;
        Spritesheet* m_Spritesheet = nullptr;
        int m_Frame = 0;
        double m_FrameRate = 0.0;
        double m_Timer = 0.0;
        bool m_UsingSpritesheet = false;
        short m_Dir = 1;
        bool m_UsingInvertDir = false;
    };

}