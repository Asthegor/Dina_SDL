#include "dinapch.h"
#include "LevelManager.h"

namespace Dina
{
	LevelManager* LevelManager::s_Instance = nullptr;

	LevelManager* LevelManager::GetInstance()
	{
		if (!s_Instance)
			s_Instance = new LevelManager();
		
		return s_Instance;
	}
	void LevelManager::AddLevel(const char* levelName, const char* fileName)
	{
		Level* level = new Level(fileName);
		GetInstance()->m_Levels.emplace(levelName, level);
	}
	void LevelManager::RemoveLevel(const char* levelName)
	{
		GetInstance()->m_Levels.erase(levelName);
	}
	void LevelManager::SetCurrentLevel(const char* levelName)
	{
		GetInstance()->m_CurrentLevel = GetInstance()->m_Levels.at(levelName);
	}
	LevelManager::~LevelManager()
	{
		for (auto it = m_Levels.rbegin(); it != m_Levels.rend(); ++it)
		{
			delete (*it).second;
			m_Levels.erase((*it).first);
		}
	}
}