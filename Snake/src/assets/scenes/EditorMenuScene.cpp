#include "EditorMenuScene.h"

#include "assets/scripts/ButtonScript.h"
#include "assets/scripts/EditorMenuScript.h"

EditorMenuScene::EditorMenuScene(Nigozi::SceneManager* sceneManager)
	:Scene(sceneManager)
{
	Nigozi::Entity loadButton = CreateEntity("Load", "LoadButton");
	loadButton.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/load.png", glm::vec2(0.0f));
	loadButton.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(loadButton));
	auto& loadTransform = loadButton.GetComponent<Nigozi::TransformComponent>();
	loadTransform.Scale = glm::vec2(5.0f, 2.5f);
	loadTransform.Position = glm::vec2(0.0f, 3.0f);

	Nigozi::Entity newButton = CreateEntity("New", "NewButton");
	newButton.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/new.png", glm::vec2(0.0f));
	newButton.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(newButton));
	auto& newTransform = newButton.GetComponent<Nigozi::TransformComponent>();
	newTransform.Scale = glm::vec2(5.0f, 2.5f);
	newTransform.Position = glm::vec2(0.0f, 0.0f);

	Nigozi::Entity backButton = CreateEntity("Back", "BackButton");
	backButton.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/back.png", glm::vec2(0.0f));
	backButton.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(backButton));
	auto& backTransform = backButton.GetComponent<Nigozi::TransformComponent>();
	backTransform.Scale = glm::vec2(5.0f, 2.5f);
	backTransform.Position = glm::vec2(0.0f, -3.0f);

	Nigozi::Entity menuManager = CreateEntity("Menu", "MenuManager");
	menuManager.AddComponent<Nigozi::ScriptComponent>(std::make_shared<EditorMenuScript>(menuManager));
}

EditorMenuScene::~EditorMenuScene()
{
}
