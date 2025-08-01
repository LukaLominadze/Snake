#include "EditorScene.h"

#include "assets/scripts/ButtonScript.h"
#include "assets/scripts/EditorScript.h"

EditorScene::EditorScene(Nigozi::SceneManager* sceneManager)
	:Scene(sceneManager)
{
	float aspect = Nigozi::Window::GetGlobalWindowData().Width / (float)Nigozi::Window::GetGlobalWindowData().Height;

	Nigozi::Entity background = CreateEntity("Background", "Background");
	auto& sprite = background.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/background.png", glm::vec2(0.0f, 0.0f), -2);
	sprite.Color = glm::vec4(0.2f, 0.55f, 0.25f, 1.0f);
	auto& transform = background.GetComponent<Nigozi::TransformComponent>();
	transform.Scale = glm::vec2(12.0f * aspect, 12.0f);
	transform.Position = glm::vec2(0.0f, -0.5f);

	Nigozi::Entity backButton = CreateEntity("Back", "BackButton");
	backButton.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/back.png", glm::vec2(0.0f));
	backButton.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(backButton));
	auto& backTransform = backButton.GetComponent<Nigozi::TransformComponent>();
	backTransform.Scale = glm::vec2(3.0f, 1.5f);
	backTransform.Position = glm::vec2(-aspect * 6.0f + 2.0f, 4.5f);

	Nigozi::Entity wallSwatch = CreateEntity("WallSwatch", "WallSwatch");
	wallSwatch.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/wall.png", glm::vec2(0.0f));
	wallSwatch.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(wallSwatch));
	auto& wallTransform = wallSwatch.GetComponent<Nigozi::TransformComponent>();
	wallTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, 3.0f);

	Nigozi::Entity floorSwatch = CreateEntity("FloorSwatch", "FloorSwatch");
	floorSwatch.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/floor.png", glm::vec2(0.0f));
	floorSwatch.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(floorSwatch));
	auto& floorTransform = floorSwatch.GetComponent<Nigozi::TransformComponent>();
	floorTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, 1.5f);

	Nigozi::Entity brushSwatch = CreateEntity("BrushSwatch", "BrushSwatch");
	brushSwatch.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/cursor.png", glm::vec2(0.0f));
	brushSwatch.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(brushSwatch));
	auto& brushTransform = brushSwatch.GetComponent<Nigozi::TransformComponent>();
	brushTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, 0.0f);

	Nigozi::Entity eraserSwatch = CreateEntity("EraserSwatch", "EraserSwatch");
	eraserSwatch.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/eraser.png", glm::vec2(0.0f));
	eraserSwatch.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(eraserSwatch));
	auto& eraserTransform = eraserSwatch.GetComponent<Nigozi::TransformComponent>();
	eraserTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, -1.5f);

	Nigozi::Entity playerSwatch = CreateEntity("PlayerSwatch", "PlayerSwatch");
	playerSwatch.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/snake-head.png", glm::vec2(0.0f));
	playerSwatch.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(playerSwatch));
	auto& playerTransform = playerSwatch.GetComponent<Nigozi::TransformComponent>();
	playerTransform.Position = glm::vec2(-aspect * 6.0f + 1.0f, -3.0f);

	Nigozi::Entity brush = CreateEntity("Brush", "Brush");
	brush.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/cursor.png", glm::vec2(0.0f));

	Nigozi::Entity eraser = CreateEntity("Eraser", "Eraser");
	eraser.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/eraser.png", glm::vec2(0.0f));

	Nigozi::Entity playerTool = CreateEntity("PlayerTool", "PlayerTool");
	playerTool.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/snake-head.png", glm::vec2(0.0f), -3);

	Nigozi::Entity player = CreateEntity("Player", "Player");
	player.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/snake-head.png", glm::vec2(0.0f), 1);

	Nigozi::Entity editorManager = CreateEntity("Manager", "EditorManager");
	editorManager.AddComponent<Nigozi::ScriptComponent>(std::make_shared<EditorScript>(editorManager));
}

EditorScene::~EditorScene()
{
}
