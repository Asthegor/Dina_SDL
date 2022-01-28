#pragma once
#include "Dina/Core/Component.h"

namespace Dina
{
    class DINA_API Level : public Component
    {
    public:
        Level(const char* fileName);

        // Hérité via Component
        virtual void Load() override;
        virtual void Update(double deltatime) override;
        virtual void Draw() override;

    private:
        std::string m_FileName;



    };

}