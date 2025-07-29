#pragma once

#include <Nigozi.h>
#include "misc/Event.h"
#include <filesystem>

class LevelManagerScript : public Nigozi::Script
{
public:
	LevelManagerScript(Nigozi::Entity entity);
	~LevelManagerScript();

	virtual void OnEvent(Nigozi::Event& event);
	virtual void OnUpdate(float timestep) override;

	void UnloadCurrentLevel();
	void LoadLevel(std::filesystem::path filePath);

	void AddScore();

	void AddOnStepListener(Observer* listener);
	void RemoveOnStepListener(Observer* listener);
	void AddOnLevelLoadedListener(Observer* listener);
	void RemoveOnLevelLoadedListener(Observer* listener);

	inline const glm::vec2 GetMapSize() const { return m_mapSize; }
	inline const std::vector<glm::vec2>& GetFloorPositions() const { return m_floorPositions; }
	inline const glm::vec2 GetPlayerSpawnPosition() const { return m_playerSpawn; }
private:
	bool OnWindowResizedEvent(Nigozi::WindowResizedEvent& event);
private:
	Nigozi::Entity m_scoreDigit1Entity, m_scoreDigit2Entity, m_backgroundEntity;
	Nigozi::Entity m_finishedLevelTextEntity, m_wonGameTextEntity;

	Event m_onStep, m_onLevelLoaded;

	std::shared_ptr<Nigozi::Texture> p_numberAtlas;
	std::shared_ptr<Nigozi::SubTexture> p_scoreDigit1SubTexture, p_scoreDigit2SubTexture;

	glm::vec2 m_playerSpawn = glm::vec2(0.0f), m_mapSize;
	glm::vec4 m_backgroundColor = glm::vec4(0.2f, 0.6f, 0.1f, 1.0f);

	std::vector<std::filesystem::path> m_levels;
	std::vector<glm::vec2> m_floorPositions;
	std::vector<Nigozi::Entity> m_map;

	float m_stepTime = 0.25f;
	float m_pauseAfterCompletionTime = 3.0f;
	float m_destoryMapInteral = 0.0f;
	float m_elapsedTime = 0.0f;

	uint32_t m_score = 0, m_pointsToWin;

	bool m_completedLevel = false, m_won = false;
};

