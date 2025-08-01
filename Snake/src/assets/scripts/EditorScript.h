#pragma once

#include <Nigozi.h>

#include "misc/Observer.h"
#include "misc/NFDUtils.h"
#include "misc/StringUtils.h"

enum class Tool {
	ERASER = 0,
	BRUSH = 1,
	PLAYER = 2,
};

enum class TileType {
	FLOOR = 0,
	WALL = 1,
	PLAYER = 2
};

enum class WallState {
	HIDDEN = -3,
	SHOWN = 0
};

class EditorScript : public Nigozi::Script
{
public:
	EditorScript(Nigozi::Entity entity);
	~EditorScript();

	void OnEvent(Nigozi::Event& event) override;
	void OnUpdate(float timestep) override;
	void OnImGuiRender() override;

	bool LoadLevel();
	void LoadDefault();
private:
	bool OnWindowResizedEvent(Nigozi::WindowResizedEvent& event);

	void SaveLevel();
private:
	Observer m_onBackPressed, m_onWallSwatchPressed, m_onFloorSwatchPressed,
			 m_onBrushSwatchPressed, m_onEraserSwatchPressed, m_onPlayerSwatchPressed;

	Nigozi::Entity m_background, m_backButton, m_brushSwatch, m_eraserSwatch,
				   m_brush, m_eraser, m_wallSwatch, m_floorSwatch, m_playerSwatch, m_playerTool, m_player;

	glm::vec4 m_wallSpriteColor = glm::vec4(0.0f, 1.0f, 0.3f, 1.0f);
	glm::vec4 m_floorSpriteColor = glm::vec4(1.0f);

	Tool m_selectedTool;

	glm::vec2 m_tileOffset, m_playerSpawn;

	std::string m_levelName;
	std::filesystem::path m_savePath, m_defaultSaveDirectory = "src\\assets\\levels\\";

	int m_width = 0, m_height = 0;
	uint32_t m_pointsToWin;
	std::vector<int> m_map;
};

