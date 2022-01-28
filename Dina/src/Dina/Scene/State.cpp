#include "dinapch.h"
#include "State.h"

namespace Dina
{
	State::State(std::string name, Component* component) : name(name), component(component), isLoaded(false)
	{
	}

	void State::Load()
	{
		if (!isLoaded)
		{
			if (component)
				component->Load();
			isLoaded = true;
		}
	}

	void State::Update(double deltatime)
	{
		if (component)
			component->Update(deltatime);
	}

	State::~State()
	{
	}

	void State::Draw()
	{
		if (component)
			component->Draw();
	}
}