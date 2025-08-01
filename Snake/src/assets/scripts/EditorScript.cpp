#include "EditorScript.h"

#include "misc/NFDUtils.h"
#include "yaml-cpp/yaml.h"

#include "assets/scripts/ButtonScript.h"
#include "layers/SnakeLayer.h"

EditorScript::EditorScript(Nigozi::Entity entity)
	:Script(entity),
	m_onBackPressed([this]() {
		m_entityHandle.GetScene()->GetSceneManager()->QueueLoadScene("MainMenu");
	}),
	m_onWallSwatchPressed([this]() {
		std::filesystem::path newWallTexturePath = NFDUtils::OpenFileDialog("png;jpg;jpeg");
		if (!newWallTexturePath.empty()) {
			std::string path = newWallTexturePath.string();

			auto& wallSprite = m_wallSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
			wallSprite.SpriteTexture.reset();
			wallSprite.Sprite.reset();
			wallSprite.SpriteTexture = std::make_shared<Nigozi::Texture>(path);
			wallSprite.Sprite = std::make_shared<Nigozi::SubTexture>(wallSprite.SpriteTexture, glm::vec2(0.0f));
			wallSprite.Color = m_wallSpriteColor;
			std::vector<Nigozi::Entity> walls = m_entityHandle.GetScene()->TryGetEntitiesByTag("Wall");
			for (auto wall : walls) {
				auto& sprite = wall.GetComponent<Nigozi::SpriteRendererComponent>();
				sprite.SpriteTexture = wallSprite.SpriteTexture;
				sprite.Sprite = wallSprite.Sprite;
				sprite.Color = wallSprite.Color;
			}
		}
	}),
	m_onFloorSwatchPressed([this]() {
	std::filesystem::path newFloorTexturePath = NFDUtils::OpenFileDialog("png;jpg;jpeg");
		if (!newFloorTexturePath.empty()) {
			std::string path = newFloorTexturePath.string();

			auto& floorSprite = m_floorSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
			floorSprite.SpriteTexture.reset();
			floorSprite.Sprite.reset();
			floorSprite.SpriteTexture = std::make_shared<Nigozi::Texture>(path);
			floorSprite.Color = m_floorSpriteColor;
			floorSprite.Sprite = std::make_shared<Nigozi::SubTexture>(floorSprite.SpriteTexture, glm::vec2(0.0f));
			std::vector<Nigozi::Entity> floors = m_entityHandle.GetScene()->TryGetEntitiesByTag("Floor");
			for (auto floor : floors) {
				auto& sprite = floor.GetComponent<Nigozi::SpriteRendererComponent>();
				sprite.SpriteTexture = floorSprite.SpriteTexture;
				sprite.Sprite = floorSprite.Sprite;
				sprite.Color = floorSprite.Color;
			}
		}
	}),
	m_onBrushSwatchPressed([this]() {
		auto& brushSprite = m_brush.GetComponent<Nigozi::SpriteRendererComponent>();
		auto& eraserSprite = m_eraser.GetComponent<Nigozi::SpriteRendererComponent>();
		auto& playerToolSprite = m_playerTool.GetComponent<Nigozi::SpriteRendererComponent>();
		brushSprite.ZOrder = 1;
		eraserSprite.ZOrder = -3;
		playerToolSprite.ZOrder = -3;
		m_selectedTool = Tool::BRUSH;
	}),
	m_onEraserSwatchPressed([this]() {
		auto& brushSprite = m_brush.GetComponent<Nigozi::SpriteRendererComponent>();
		auto& eraserSprite = m_eraser.GetComponent<Nigozi::SpriteRendererComponent>();
		auto& playerToolSprite = m_playerTool.GetComponent<Nigozi::SpriteRendererComponent>();
		eraserSprite.ZOrder = 1;
		brushSprite.ZOrder = -3;
		playerToolSprite.ZOrder = -3;
		m_selectedTool = Tool::ERASER;
	}),
	m_onPlayerSwatchPressed([this]() {
		auto& brushSprite = m_brush.GetComponent<Nigozi::SpriteRendererComponent>();
		auto& eraserSprite = m_eraser.GetComponent<Nigozi::SpriteRendererComponent>();
		auto& playerToolSprite = m_playerTool.GetComponent<Nigozi::SpriteRendererComponent>();
		playerToolSprite.ZOrder = 1;
		brushSprite.ZOrder = -3;
		eraserSprite.ZOrder = -3;
		m_selectedTool = Tool::PLAYER;
	}),
	m_selectedTool(Tool::BRUSH)
{
	m_background = m_entityHandle.GetScene()->TryGetEntityByTag("Background");
	m_backButton = m_entityHandle.GetScene()->TryGetEntityByTag("BackButton");
	m_wallSwatch = m_entityHandle.GetScene()->TryGetEntityByTag("WallSwatch");
	m_floorSwatch = m_entityHandle.GetScene()->TryGetEntityByTag("FloorSwatch");
	m_brushSwatch = m_entityHandle.GetScene()->TryGetEntityByTag("BrushSwatch");
	m_eraserSwatch = m_entityHandle.GetScene()->TryGetEntityByTag("EraserSwatch");
	m_playerSwatch = m_entityHandle.GetScene()->TryGetEntityByTag("PlayerSwatch");
	m_brush = m_entityHandle.GetScene()->TryGetEntityByTag("Brush");
	m_eraser = m_entityHandle.GetScene()->TryGetEntityByTag("Eraser");
	m_playerTool = m_entityHandle.GetScene()->TryGetEntityByTag("PlayerTool");

	auto& brushSprite = m_brush.GetComponent<Nigozi::SpriteRendererComponent>();
	auto& eraserSprite = m_eraser.GetComponent<Nigozi::SpriteRendererComponent>();
	brushSprite.ZOrder = 1;
	eraserSprite.ZOrder = -3;

	auto& backButtonScript = m_backButton.GetComponent<Nigozi::ScriptComponent>();
	auto& wallSwatchScript = m_wallSwatch.GetComponent<Nigozi::ScriptComponent>();
	auto& floorSwatchScript = m_floorSwatch.GetComponent<Nigozi::ScriptComponent>();
	auto& brushSwatchScript = m_brushSwatch.GetComponent<Nigozi::ScriptComponent>();
	auto& eraserSwatchScript = m_eraserSwatch.GetComponent<Nigozi::ScriptComponent>();
	auto& playerSwatchScript = m_playerSwatch.GetComponent<Nigozi::ScriptComponent>();

	((ButtonScript*)(backButtonScript.ScriptHandle.get()))->AddOnPressedListener(&m_onBackPressed);
	((ButtonScript*)(wallSwatchScript.ScriptHandle.get()))->AddOnPressedListener(&m_onWallSwatchPressed);
	((ButtonScript*)(floorSwatchScript.ScriptHandle.get()))->AddOnPressedListener(&m_onFloorSwatchPressed);
	((ButtonScript*)(brushSwatchScript.ScriptHandle.get()))->AddOnPressedListener(&m_onBrushSwatchPressed);
	((ButtonScript*)(eraserSwatchScript.ScriptHandle.get()))->AddOnPressedListener(&m_onEraserSwatchPressed);
	((ButtonScript*)(playerSwatchScript.ScriptHandle.get()))->AddOnPressedListener(&m_onPlayerSwatchPressed);

	auto& wallSprite = m_wallSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
	wallSprite.Color = m_wallSpriteColor;

	if (!LoadLevel()) {
		LoadDefault();
	}
}

EditorScript::~EditorScript()
{
}

void EditorScript::OnEvent(Nigozi::Event& event)
{
	Nigozi::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Nigozi::WindowResizedEvent>(std::bind(&EditorScript::OnWindowResizedEvent, this, std::placeholders::_1));
}

void EditorScript::OnUpdate(float timestep)
{
	glm::vec2 position = SnakeLayer::GetMainCamera().GetMousePositionWorldSpace();
	if (m_selectedTool == Tool::BRUSH) {
		auto& brushTransform = m_brush.GetComponent<Nigozi::TransformComponent>();
		brushTransform.Position = position + glm::vec2(0.49f, -0.49f);
	}
	else if (m_selectedTool == Tool::ERASER) {
		auto& eraserTransform = m_eraser.GetComponent<Nigozi::TransformComponent>();
		eraserTransform.Position = position + glm::vec2(0.49f, -0.49f);
	}
	else if (m_selectedTool == Tool::PLAYER) {
		auto& playerToolTransform = m_playerTool.GetComponent<Nigozi::TransformComponent>();
		playerToolTransform.Position = position;
	}

	if (!Nigozi::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
		return;
	}
	glm::vec2 mousePosition = glm::round(SnakeLayer::GetMainCamera().GetMousePositionWorldSpace());
	if (glm::abs(mousePosition.x) > m_width / 2.0f || glm::abs(mousePosition.y) > m_height / 2.0f ||
		mousePosition.x > m_width / 2.0f - 1 || mousePosition.y > m_height / 2.0f - 1) {
		return;
	}

	if (m_selectedTool == Tool::BRUSH) {
		std::vector<Nigozi::Entity> walls = m_entityHandle.GetScene()->TryGetEntitiesByTag("Wall");
		for (auto wall : walls) {
			auto& transform = wall.GetComponent<Nigozi::TransformComponent>();
			glm::vec2 diff = glm::abs(transform.Position - mousePosition);
			if (diff.x > 0.1f || diff.y > 0.1f) {
				continue;
			}
			glm::vec2 localPosition = transform.Position + m_tileOffset;
			if (m_map[localPosition.y * m_width + localPosition.x] == (int)TileType::PLAYER) {
				continue;
			}

			auto& sprite = wall.GetComponent<Nigozi::SpriteRendererComponent>();
			sprite.ZOrder = (int)WallState::SHOWN;
			m_map[localPosition.y * m_width + localPosition.x] = (int)TileType::WALL;
		}
	}
	else if (m_selectedTool == Tool::ERASER) {
		std::vector<Nigozi::Entity> walls = m_entityHandle.GetScene()->TryGetEntitiesByTag("Wall");
		for (auto wall : walls) {
			auto& transform = wall.GetComponent<Nigozi::TransformComponent>();
			glm::vec2 diff = glm::abs(transform.Position - mousePosition);
			if (diff.x > 0.1f || diff.y > 0.1f) {
				continue;
			}
			glm::vec2 localPosition = transform.Position + m_tileOffset;
			if (m_map[localPosition.y * m_width + localPosition.x] == (int)TileType::PLAYER) {
				continue;
			}

			auto& sprite = wall.GetComponent<Nigozi::SpriteRendererComponent>();
			sprite.ZOrder = (int)WallState::HIDDEN;
			m_map[localPosition.y * m_width + localPosition.x] = (int)TileType::FLOOR;
		}
	}
	else if (m_selectedTool == Tool::PLAYER) {
		glm::vec2 localPosition = mousePosition + m_tileOffset;
		if (m_map[localPosition.y * m_width + localPosition.x] == (int)TileType::WALL) {
			return;
		}
		auto& playerTransform = m_player.GetComponent<Nigozi::TransformComponent>();
		glm::vec2 localPlayerPosition = playerTransform.Position + m_tileOffset;
		m_map[localPlayerPosition.y * m_width + localPlayerPosition.x] = (int)TileType::FLOOR;
		playerTransform.Position = mousePosition;
		m_map[localPosition.y * m_width + localPosition.x] = (int)TileType::PLAYER;
	}
}

void EditorScript::OnImGuiRender()
{
	ImGui::Begin("Parameters");
	if (ImGui::InputText("Name", (char*)m_levelName.c_str(), 32)) {
		m_levelName = m_levelName.c_str();
	}
	if (ImGui::ColorEdit4("Wall Color", (float*)(&m_wallSpriteColor))) {
		auto& wallSprite = m_wallSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
		wallSprite.Color = m_wallSpriteColor;
		std::vector<Nigozi::Entity> walls = m_entityHandle.GetScene()->TryGetEntitiesByTag("Wall");
		for (auto entity : walls) {
			auto& sprite = entity.GetComponent<Nigozi::SpriteRendererComponent>();
			sprite.Color = wallSprite.Color;
		}
	}
	if (ImGui::ColorEdit4("Floor Color", (float*)(&m_floorSpriteColor))) {
		auto& floorSprite = m_floorSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
		floorSprite.Color = m_floorSpriteColor;
		std::vector<Nigozi::Entity> floors = m_entityHandle.GetScene()->TryGetEntitiesByTag("Floor");
		for (auto entity : floors) {
			auto& sprite = entity.GetComponent<Nigozi::SpriteRendererComponent>();
			sprite.Color = floorSprite.Color;
		}
	}
	ImGui::DragInt("Points To Win", (int*)&m_pointsToWin, 1, 0, 99);
	if (ImGui::Button("Save")) {
		LOG(m_defaultSaveDirectory.string() + m_levelName + ".yaml");
		if (std::filesystem::path(m_defaultSaveDirectory.string() + m_levelName + ".yaml").compare(m_savePath) != 0) {
			LOG(m_savePath << " <- Need to rename!");
			std::filesystem::rename(m_savePath, std::filesystem::path(m_defaultSaveDirectory).append(m_levelName + ".yaml"));
			m_savePath.replace_filename(m_levelName + ".yaml");
		}
		SaveLevel();
	}
	if (ImGui::Button("Save As New")) {
		if (m_levelName + ".yaml" == m_savePath.filename().string()) {
			LOG("rename to save as new");
			m_levelName.append("_");
			m_savePath.replace_filename(m_levelName + ".yaml");
		}
		SaveLevel();
	}
	ImGui::End();
	//static bool show = true;
	//ImGui::ShowDemoWindow(&show);
}

bool EditorScript::LoadLevel()
{
	std::filesystem::path levelPath;
	YAML::Node cacheData = YAML::LoadFile("src/assets/editor/editorCache.yaml");
	if (!cacheData.IsNull()) {
		levelPath = cacheData["CurrentLevel"].as<std::string>();
	}
	if (levelPath.empty() || levelPath.string() == "NONE") {
		return false;
	}
	std::filesystem::path levelRootPath = std::filesystem::path(levelPath).remove_filename();
	
	/*
	*  All levels in the game are loaded from the src / assets / levels directory
	*  If the picked file isn't from this directory, copy it.
	*/
	if (levelRootPath.remove_filename().compare(std::filesystem::absolute(m_defaultSaveDirectory)) != 0) {
		std::filesystem::path copyPath = std::filesystem::path(m_defaultSaveDirectory).append(levelPath.filename().string());
		for (const auto& entry : std::filesystem::directory_iterator(m_defaultSaveDirectory))
		{
			if (std::filesystem::path(entry).compare(copyPath) == 0)
			{
				std::string newName = StringUtils::SplitString(levelPath.filename().string(), ".")[0] + "_.yaml";
				copyPath = copyPath.remove_filename().append(newName);
			}
		}
		std::filesystem::copy_file(levelPath, copyPath);
		levelPath = copyPath;	
	}
	m_levelName = StringUtils::SplitString(levelPath.filename().string(), ".")[0];
	m_savePath = std::filesystem::relative(levelPath);

	m_map.resize(m_width * m_height);

	YAML::Node data = YAML::LoadFile(levelPath.string());
	YAML::Node rootNode = data["Level"];

	YAML::Node assetsNode = rootNode["Assets"];

	std::string wallPath = assetsNode["Wall"]["Path"].as<std::string>();
	std::string floorPath = assetsNode["Floor"]["Path"].as<std::string>();

	auto& wallSprite = m_wallSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
	auto& floorSprite = m_floorSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
	wallSprite.SpriteTexture.reset();
	wallSprite.SpriteTexture = std::make_shared<Nigozi::Texture>(wallPath);
	wallSprite.Sprite = std::make_shared<Nigozi::SubTexture>(wallSprite.SpriteTexture, glm::vec2(0.0f));
	floorSprite.SpriteTexture.reset();
	floorSprite.SpriteTexture = std::make_shared<Nigozi::Texture>(floorPath);
	floorSprite.Sprite = std::make_shared<Nigozi::SubTexture>(floorSprite.SpriteTexture, glm::vec2(0.0f));
	
	std::vector<float> wallColorVec = assetsNode["Wall"]["Color"].as<std::vector<float>>();
	std::vector<float> floorColorVec = assetsNode["Floor"]["Color"].as<std::vector<float>>();
	
	m_wallSpriteColor = glm::vec4(wallColorVec[0], wallColorVec[1], wallColorVec[2], wallColorVec[3]);
	m_floorSpriteColor = glm::vec4(floorColorVec[0], floorColorVec[1], floorColorVec[2], floorColorVec[3]);

	wallSprite.Color = m_wallSpriteColor;
	floorSprite.Color = m_floorSpriteColor;

	m_width = rootNode["Width"].as<int>();
	m_height = rootNode["Height"].as<int>();
	
	m_pointsToWin = rootNode["PointsToWin"].as<uint32_t>();
	
	m_map = rootNode["Map"].as<std::vector<int>>();
	
	m_tileOffset = glm::vec2(m_width / 2.0f, m_height / 2.0f);
	m_playerSpawn = glm::vec2(0.0f);
	
	for (size_t y = 0; y < m_map.size() / m_width; y++) {
		for (size_t x = 0; x < m_width; x++) {
			TileType type = static_cast<TileType>(m_map[y * m_width + x]);

			// We will pregenerate all of the walls and floors and just reuse them when we need to
			
			Nigozi::Entity floor = m_entityHandle.GetScene()->CreateEntity("Floor", "Floor");
			auto& _floorSprite = floor.AddComponent<Nigozi::SpriteRendererComponent>(floorSprite.SpriteTexture, floorSprite.Sprite, -1);
			_floorSprite.Color = floorSprite.Color;
			auto& _floorTransform = floor.GetComponent<Nigozi::TransformComponent>();
			_floorTransform.Position = glm::vec2(x - m_tileOffset.x, y - m_tileOffset.y);

			Nigozi::Entity wall = m_entityHandle.GetScene()->CreateEntity("Wall", "Wall");
			auto& _wallSprite = wall.AddComponent<Nigozi::SpriteRendererComponent>(wallSprite.SpriteTexture, wallSprite.Sprite, (int8_t)WallState::HIDDEN);
			_wallSprite.Color = wallSprite.Color;
			auto& transform = wall.GetComponent<Nigozi::TransformComponent>();
			transform.Position = glm::vec2(x - m_tileOffset.x, y - m_tileOffset.y);

			if (type == TileType::WALL)
			{
				_wallSprite.ZOrder = (int)WallState::SHOWN;
			}
			else if (type == TileType::PLAYER) {
				m_playerSpawn = glm::vec2(x - m_tileOffset.x, y - m_tileOffset.y);

				m_player = m_entityHandle.GetScene()->TryGetEntityByTag("Player");
				m_player.GetComponent<Nigozi::TransformComponent>().Position = m_playerSpawn;
			}
		}
	}
	return true;
}

void EditorScript::LoadDefault()
{
	m_levelName = "newlevel";
	
	for (const auto& entry : std::filesystem::directory_iterator(m_defaultSaveDirectory))
	{
		if (std::filesystem::path(entry).compare(std::filesystem::path(m_defaultSaveDirectory.string() + m_levelName + ".yaml")) == 0)
		{
			m_levelName.append("_");
		}
	}

	m_savePath = std::filesystem::path(m_defaultSaveDirectory).append(m_levelName + ".yaml");

	auto& wallSprite = m_wallSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
	auto& floorSprite = m_floorSwatch.GetComponent<Nigozi::SpriteRendererComponent>();

	m_width = 12;
	m_height = 12;

	m_pointsToWin = 10;

	m_map.resize(m_width * m_height);
	for (size_t i = 0; i < m_map.size(); i++) {
		m_map[i] = (int)TileType::FLOOR;
	}
	m_map[(m_height / 2) * m_width + (m_width / 2)] = (int)TileType::PLAYER;

	m_tileOffset = glm::vec2(m_width / 2.0f, m_height / 2.0f);
	m_playerSpawn = glm::vec2(0.0f);


	for (size_t y = 0; y < m_map.size() / m_width; y++) {
		for (size_t x = 0; x < m_width; x++) {
			TileType type = static_cast<TileType>(m_map[y * m_width + x]);

			// We will pregenerate all of the walls and floors and just reuse them when we need to

			Nigozi::Entity floor = m_entityHandle.GetScene()->CreateEntity("Floor", "Floor");
			auto& _floorSprite = floor.AddComponent<Nigozi::SpriteRendererComponent>(floorSprite.SpriteTexture, floorSprite.Sprite, -1);
			_floorSprite.Color = floorSprite.Color;
			auto& _floorTransform = floor.GetComponent<Nigozi::TransformComponent>();
			_floorTransform.Position = glm::vec2(x - m_tileOffset.x, y - m_tileOffset.y);

			Nigozi::Entity wall = m_entityHandle.GetScene()->CreateEntity("Wall", "Wall");
			auto& _wallSprite = wall.AddComponent<Nigozi::SpriteRendererComponent>(wallSprite.SpriteTexture, wallSprite.Sprite, (int)WallState::HIDDEN);
			_wallSprite.Color = wallSprite.Color;
			auto& transform = wall.GetComponent<Nigozi::TransformComponent>();
			transform.Position = glm::vec2(x - m_tileOffset.x, y - m_tileOffset.y);

			if (type == TileType::PLAYER) {
				m_playerSpawn = glm::vec2(x - m_tileOffset.x, y - m_tileOffset.y);

				m_player = m_entityHandle.GetScene()->TryGetEntityByTag("Player");
				m_player.GetComponent<Nigozi::TransformComponent>().Position = m_playerSpawn;
			}
		}
	}
}

bool EditorScript::OnWindowResizedEvent(Nigozi::WindowResizedEvent& event)
{
	float aspect = event.GetWidth() / (float)event.GetHeight();

	auto& backgroundTransform = m_background.GetComponent<Nigozi::TransformComponent>();
	auto& backButtonTransform = m_backButton.GetComponent<Nigozi::TransformComponent>();
	auto& wallTransform = m_wallSwatch.GetComponent<Nigozi::TransformComponent>();
	auto& floorTransform = m_floorSwatch.GetComponent<Nigozi::TransformComponent>();
	auto& brushSwatchTransform = m_brushSwatch.GetComponent<Nigozi::TransformComponent>();
	auto& eraserSwatchTransform = m_eraserSwatch.GetComponent<Nigozi::TransformComponent>();
	auto& playerSwatchTransform = m_playerSwatch.GetComponent<Nigozi::TransformComponent>();
	backgroundTransform.Scale = glm::vec2(-aspect * 12.0f, 12.0f);
	backButtonTransform.Position = glm::vec2(-aspect * 6.0f + 2.0f, 4.5f);
	wallTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, 3.0f);
	floorTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, 1.5f);
	brushSwatchTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, 0.0f);
	eraserSwatchTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, -1.5f);
	playerSwatchTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, -3.0f);

	return false;
}

void EditorScript::SaveLevel()
{
	YAML::Emitter out;
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Level" << YAML::Value;

		out << YAML::BeginMap;
		out << YAML::Key << "Assets" << YAML::Value;

		out << YAML::BeginMap;

		out << YAML::Key << "Wall" << YAML::Value;
		out << YAML::BeginMap;

		auto& wallSprite = m_wallSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
		out << YAML::Key << "Path" << YAML::Value << wallSprite.SpriteTexture->GetPath().c_str();
		out << YAML::Key << "Color" << YAML::Value << std::vector<float>{
			m_wallSpriteColor.x, m_wallSpriteColor.y, m_wallSpriteColor.z, m_wallSpriteColor.w
		};
		out << YAML::EndMap;

		out << YAML::Key << "Floor" << YAML::Value;
		out << YAML::BeginMap;

		auto& floorSprite = m_floorSwatch.GetComponent<Nigozi::SpriteRendererComponent>();
		out << YAML::Key << "Path" << YAML::Value << floorSprite.SpriteTexture->GetPath();
		out << YAML::Key << "Color" << YAML::Value << std::vector<float>{
			m_floorSpriteColor.x, m_floorSpriteColor.y, m_floorSpriteColor.z, m_floorSpriteColor.w
		};
		out << YAML::EndMap;

		out << YAML::EndMap;
			
		out << YAML::Key << "Width" << YAML::Value << m_width;
		out << YAML::Key << "Height" << YAML::Value << m_height;
		out << YAML::Key << "PointsToWin" << YAML::Value << m_pointsToWin;

		out << YAML::Key << "Map" << YAML::Value << m_map;

		out << YAML::EndMap;

		out << YAML::EndMap;
	}
	
	{
		std::ofstream fout(m_savePath);
		fout << out.c_str();
	}

	LOG("Saved level! -> " << m_savePath.string());
}
