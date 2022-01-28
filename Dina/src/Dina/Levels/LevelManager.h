#pragma once
#include "Dina/Core/Component.h"
#include "Level.h"

namespace Dina
{
	class DINA_API LevelManager
	{
	public:
		LevelManager& operator=(const LevelManager&) = delete;
		LevelManager(const LevelManager&) = delete;

		static void AddLevel(const char* levelName, const char* fileName);
		static void RemoveLevel(const char* levelName);
		static void SetCurrentLevel(const char* levelName);
		~LevelManager();

	private:
		static LevelManager* GetInstance();
		static LevelManager* s_Instance;
		LevelManager() = default;

		std::string m_FileName;
		std::map<const char*, Level*> m_Levels;
		Level* m_CurrentLevel = nullptr;
	};
}