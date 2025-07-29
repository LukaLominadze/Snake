#include "LevelManagerScript.h"
#include "yaml-cpp/yaml.h"
#include "fstream"

LevelManagerScript::LevelManagerScript(Nigozi::Entity entity)
	:Script(entity),
	p_numberAtlas(std::make_shared<Nigozi::Texture>("src/assets/sprites/numbers.png")),
	p_scoreDigit1SubTexture(std::make_shared<Nigozi::SubTexture>(p_numberAtlas, glm::vec2(128.0f, 128.0f), 1, 0)),
	p_scoreDigit2SubTexture(std::make_shared<Nigozi::SubTexture>(p_numberAtlas, glm::vec2(128.0f, 128.0f), 0, 0))
{
	m_scoreDigit1Entity = m_entityHandle.GetScene()->CreateEntity("Score0", "Score");
	m_scoreDigit1Entity.AddComponent<Nigozi::SpriteRendererComponent>(p_numberAtlas, p_scoreDigit1SubTexture);
	auto& transform1 = m_scoreDigit1Entity.GetComponent<Nigozi::TransformComponent>();
	transform1.Position.y = 5.0f;
	transform1.Position.x = 0.5f;

	m_scoreDigit2Entity = m_entityHandle.GetScene()->CreateEntity("Score1", "Score");
	m_scoreDigit2Entity.AddComponent<Nigozi::SpriteRendererComponent>(p_numberAtlas, p_scoreDigit2SubTexture);
	auto& transform2 = m_scoreDigit2Entity.GetComponent<Nigozi::TransformComponent>();
	transform2.Position.y = 5.0f;
	transform2.Position.x = 0.0f;

	m_backgroundEntity = m_entityHandle.GetScene()->CreateEntity("Background", "Background");
	auto& sprite = m_backgroundEntity.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/background.png", glm::vec2(0.0f, 0.0f), -2);
	sprite.Color = glm::vec4(0.2f, 0.55f, 0.25f, 1.0f);
	float aspect = Nigozi::Window::GetGlobalWindowData().Width / (float)Nigozi::Window::GetGlobalWindowData().Height;
	auto& transform = m_backgroundEntity.GetComponent<Nigozi::TransformComponent>();
	transform.Scale = glm::vec2(12.0f * aspect, 12.0f);
	transform.Position = glm::vec2(0.0f, 0.0f);

	m_finishedLevelTextEntity = m_entityHandle.GetScene()->CreateEntity("LevelCompleted", "Text");
	m_finishedLevelTextEntity.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/level-completed.png", glm::vec2(0.0f), -3);
	auto& levelFinishTransform = m_finishedLevelTextEntity.GetComponent<Nigozi::TransformComponent>();
	levelFinishTransform.Scale = glm::vec2(8.0f, 1.0f);
	
	m_wonGameTextEntity = m_entityHandle.GetScene()->CreateEntity("YouWon", "Text");
	m_wonGameTextEntity.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/you-won.png", glm::vec2(0.0f), -3);
	auto& wonGameTransform = m_wonGameTextEntity.GetComponent<Nigozi::TransformComponent>();
	wonGameTransform.Scale = glm::vec2(8.0f, 2.0f);

	for (const auto& entry : std::filesystem::directory_iterator("src/assets/levels")) {
		m_levels.insert(m_levels.begin(), entry);
	}

	LoadLevel(m_levels[m_levels.size() - 1]);

	m_levels.pop_back();
}

LevelManagerScript::~LevelManagerScript()
{
}

void LevelManagerScript::OnEvent(Nigozi::Event& event)
{
	Nigozi::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Nigozi::WindowResizedEvent>(std::bind(&LevelManagerScript::OnWindowResizedEvent, this, std::placeholders::_1));
}

void LevelManagerScript::OnUpdate(float timestep)
{
	if (m_won)
		return;

	m_elapsedTime += timestep;
	if (!m_completedLevel && m_elapsedTime >= m_stepTime) {
		m_onStep.Invoke();
		m_elapsedTime = 0.0f;
	}

	if (m_completedLevel) {
		// Level completed animation
		if (m_elapsedTime >= m_destoryMapInteral) {
			m_map[m_map.size() - 1].Destroy();
			m_map.pop_back();
			m_elapsedTime = 0.0f;
		}
		if (m_map.empty()) {
			UnloadCurrentLevel();
			if (m_levels.empty()) {
				LOG("you win!");
				auto& textSprite = m_wonGameTextEntity.GetComponent<Nigozi::SpriteRendererComponent>();
				textSprite.ZOrder = 5;
				m_won = true;
				return;
			}
			LoadLevel(m_levels[m_levels.size() - 1]);
			m_levels.pop_back();
			m_completedLevel = false;
		}
	}
}

void LevelManagerScript::UnloadCurrentLevel()
{
	auto& textSprite = m_finishedLevelTextEntity.GetComponent<Nigozi::SpriteRendererComponent>();
	textSprite.ZOrder = -3;

	// Resetting score
	m_score = 0;
	auto& sprite1 = m_scoreDigit1Entity.GetComponent<Nigozi::SpriteRendererComponent>();
	auto& sprite2 = m_scoreDigit2Entity.GetComponent<Nigozi::SpriteRendererComponent>();
	sprite1.Sprite->SetSlot(1, 0);
	sprite2.Sprite->SetSlot(0, 0);

	m_floorPositions.clear();
}

void LevelManagerScript::LoadLevel(std::filesystem::path filePath)
{
	if (!std::filesystem::exists(filePath)) {
		LOG("File doesn't exist!");
		return;
	}

	YAML::Node data = YAML::LoadFile(filePath.string());
	YAML::Node rootNode = data["Level"];
	
	YAML::Node assetsNode = rootNode["Assets"];

	std::string wallPath = assetsNode["Wall"]["Path"].as<std::string>();
	std::string floorPath = assetsNode["Floor"]["Path"].as<std::string>();

	std::vector<float> wallColorVec = assetsNode["Wall"]["Color"].as<std::vector<float>>();
	std::vector<float> floorColorVec = assetsNode["Floor"]["Color"].as<std::vector<float>>();

	glm::vec4 wallColor(wallColorVec[0], wallColorVec[1], wallColorVec[2], wallColorVec[3]);
	glm::vec4 floorColor(floorColorVec[0], floorColorVec[1], floorColorVec[2], floorColorVec[3]);

	int width = rootNode["Width"].as<int>();
	int height = rootNode["Height"].as<int>();
	m_mapSize = glm::vec2(width, height);

	m_pointsToWin = rootNode["PointsToWin"].as<uint32_t>();

	std::vector<int> map = rootNode["Map"].as<std::vector<int>>();
	// reserving for level completion animation
	m_map.reserve(sizeof(Nigozi::Entity) * (int)map.size());

	glm::vec2 offset(width / 2.0f, height / 2.0f);
	m_playerSpawn = glm::vec2(0.0f);

	enum class TileType {
		FLOOR = 0,
		WALL = 1,
		PLAYER = 2
	};

	for (size_t y = 0; y < map.size() / width; y++) {
		for (size_t x = 0; x < width; x++) {
			TileType type = static_cast<TileType>(map[y * width + x]);
			if (type == TileType::FLOOR || type == TileType::PLAYER)
			{
				Nigozi::Entity floor = m_entityHandle.GetScene()->CreateEntity("Floor", "Map");
				m_map.push_back(floor);
				auto& sprite = floor.AddComponent<Nigozi::SpriteRendererComponent>(floorPath, glm::vec2{ 0, 0 }, -1);
				sprite.Color = floorColor;
				auto& transform = floor.GetComponent<Nigozi::TransformComponent>();
				transform.Position = glm::vec2(x - offset.x, y - offset.y);
				m_floorPositions.push_back(transform.Position);
			}
			else if (type == TileType::WALL)
			{
				Nigozi::Entity wall = m_entityHandle.GetScene()->CreateEntity("Wall", "Map");
				m_map.push_back(wall);
				auto& sprite = wall.AddComponent<Nigozi::SpriteRendererComponent>(wallPath, glm::vec2{ 0, 0 }, -1);
				sprite.Color = wallColor;
				auto& transform = wall.GetComponent<Nigozi::TransformComponent>();
				transform.Position = glm::vec2(x - offset.x, y - offset.y);
			}
			if (type == TileType::PLAYER) {
				m_playerSpawn = glm::vec2(x - offset.x, y - offset.y);
			}
		}
	}
	m_onLevelLoaded.Invoke();
}

void LevelManagerScript::AddScore()
{
	auto& sprite1 = m_scoreDigit1Entity.GetComponent<Nigozi::SpriteRendererComponent>();
	uint32_t slotX1 = sprite1.Sprite->GetSlotX();
	auto& sprite2 = m_scoreDigit2Entity.GetComponent<Nigozi::SpriteRendererComponent>();
	uint32_t slotX2 = sprite2.Sprite->GetSlotX();
	if (++slotX1 <= 10) {
		sprite1.Sprite->SetSlot(slotX1, 0);
	}
	else {
		if (slotX2 == 0)
			slotX2 = 1;
		sprite2.Sprite->SetSlot(++slotX2, 0);
		sprite1.Sprite->SetSlot(1, 0);
	}
	if (++m_score >= m_pointsToWin) {
		m_completedLevel = true;
		m_destoryMapInteral = m_pauseAfterCompletionTime / m_map.size();
		if (!m_levels.empty()) {
			auto& textSprite = m_finishedLevelTextEntity.GetComponent<Nigozi::SpriteRendererComponent>();
			textSprite.ZOrder = 5;
		}
		LOG("Next Level!");
	}
}

void LevelManagerScript::AddOnStepListener(Observer* listener)
{
	m_onStep.AddListener(listener);
}

void LevelManagerScript::RemoveOnStepListener(Observer* listener)
{
	m_onStep.RemoveListener(listener);
}

void LevelManagerScript::AddOnLevelLoadedListener(Observer* listener)
{
	m_onLevelLoaded.AddListener(listener);
}

void LevelManagerScript::RemoveOnLevelLoadedListener(Observer* listener)
{
	m_onLevelLoaded.RemoveListener(listener);
}

bool LevelManagerScript::OnWindowResizedEvent(Nigozi::WindowResizedEvent& event)
{
	float aspect = event.GetWidth() / (float)event.GetHeight();
	auto& transform = m_backgroundEntity.GetComponent<Nigozi::TransformComponent>();
	transform.Scale = glm::vec2(12.0f * aspect, 12.0f);
	return false;
}
