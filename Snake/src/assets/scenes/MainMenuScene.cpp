#include "MainMenuScene.h"
#include "assets/scripts/ButtonScript.h"
#include <assets/scripts/MainMenuScript.h>

MainMenuScene::MainMenuScene(Nigozi::SceneManager* sceneManager)
	:Scene(sceneManager)
{
	Nigozi::Renderer2D::SetClearColor(0.12f, 0.25f, 0.08f, 1.0f);

	Nigozi::Entity playButton = CreateEntity("Play", "PlayButton");
	playButton.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/play-button.png", glm::vec2{ 0.0f, 0.0f });
	playButton.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(playButton));
	auto& playTransform = playButton.GetComponent<Nigozi::TransformComponent>();
	playTransform.Scale = glm::vec2(12.0f, 6.0f);
	playTransform.Position = glm::vec2(0.0f, 2.5f);

	Nigozi::Entity editorButton = CreateEntity("Editor", "EditorButton");
	editorButton.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/editor.png", glm::vec2(0.0f));
	editorButton.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(editorButton));
	auto& editorTransform = editorButton.GetComponent<Nigozi::TransformComponent>();
	editorTransform.Scale = glm::vec2(12.0f, 5.0f);
	editorTransform.Position = glm::vec2(0.0f, -3.5f);

	Nigozi::Entity mainMenu = CreateEntity("Main", "MainMenuManager");
	mainMenu.AddComponent<Nigozi::ScriptComponent>(std::make_shared<MainMenuScript>(mainMenu));
}

MainMenuScene::~MainMenuScene()
{
}
