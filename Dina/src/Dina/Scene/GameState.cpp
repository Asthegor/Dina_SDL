#include "dinapch.h"
#include "GameState.h"
#include "Dina/Events/EventManager.h"

namespace Dina
{
	GameState* GameState::m_Instance = nullptr;

	bool GameState::IsValidState(std::string stateName) const
	{
		return states.find(stateName) != states.end();
	}

	GameState* GameState::GetInstance()
	{
		if (!m_Instance)
			m_Instance = new GameState;

		return m_Instance;
	}

	void GameState::DestroyInstance()
	{
		delete m_Instance;
		m_Instance = nullptr;
	}

	State* GameState::GetState()
	{
		return GetState(GameState::GetInstance()->currentState);
	}

	State* GameState::GetState(std::string stateName)
	{
		if (GameState::GetInstance()->IsValidState(stateName))
		{
			return GameState::GetInstance()->states.at(stateName);
		}
		return nullptr;
	}

	void GameState::AddState(std::string stateName, Component* component)
	{
		State* state = new State(stateName, component);
		GameState::GetInstance()->states.emplace(stateName, state);

	}

	void GameState::SetCurrentState(std::string stateName)
	{
		if (GameState::GetInstance()->IsValidState(stateName))
		{
			auto currentState = GetState();
			if (currentState)
			{
				EventManager::Unsubscribe(static_cast<Event*>(currentState->component));
			}
			GameState::GetInstance()->currentState = stateName;
			if (auto state = GetState())
			{
				if (!state->isLoaded)
				{
					state->Load();
					state->isLoaded = true;
				}
				EventManager::Subscribe(static_cast<Event*>(state->component));
			}
		}
	}

	void GameState::RemoveState(std::string stateName)
	{
		if (GameState::GetInstance()->IsValidState(stateName))
		{
			delete GameState::GetInstance()->states[stateName];
			GameState::GetInstance()->states.erase(stateName);
		}
	}
	void GameState::Quit()
	{
		while (GameState::GetInstance()->states.size() > 0)
		{
			auto itState = GameState::GetInstance()->states.begin();
			RemoveState((*itState).first);
		}

		DestroyInstance();
	}
}