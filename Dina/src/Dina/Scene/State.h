#pragma once
#include "Dina/Core/Component.h"
#include <string>

namespace Dina
{
	class DINA_API GameState;
	class DINA_API State : public Component
	{
		std::string name;
		Component* component;
		bool isLoaded;

		friend GameState;
	public:
		State(std::string name, Component* component);
		~State();


		// Hérité via Component
		virtual void Load() override;
		virtual void Update(double deltatime) override;
		virtual void Draw() override;


	};
}