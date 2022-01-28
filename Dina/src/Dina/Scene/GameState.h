#pragma once
#include "Dina/Core/Component.h"
#include <map>
#include <string>
#include "State.h"

namespace Dina
{
	class DINA_API GameState
	{
	public:
		static State* GetState(std::string statename);
		static State* GetState();

		static void AddState(std::string stateName, Component* object);
		static void SetCurrentState(std::string stateName);
		static void RemoveState(std::string stateName);

		static void Quit();

	public:
		GameState(const GameState&) = delete;
		GameState& operator=(const GameState&) = delete;

	private:
		GameState() = default;
		static GameState* GetInstance();
		static void DestroyInstance();
		static GameState* m_Instance;

		std::map<std::string, State*> states;
		std::string currentState;
		bool IsValidState(std::string stateName) const;
	};

}