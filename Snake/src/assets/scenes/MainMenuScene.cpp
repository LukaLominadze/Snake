#include "MainMenuScene.h"
#include "assets/scripts/ButtonScript.h"
#include <assets/scripts/MainMenuScript.h>

MainMenuScene::MainMenuScene(Nigozi::SceneManager* sceneManager)
	:Scene(sceneManager)
{
	Nigozi::Entity playButton = CreateEntity("Play", "PlayButton");
	playButton.AddComponent<Nigozi::SpriteRendererComponent>("src/Nigozi/res/textures/flatQuad.png", glm::vec2{ 0.0f, 0.0f });
	playButton.AddComponent<Nigozi::ScriptComponent>(std::make_shared<ButtonScript>(playButton));
	playButton.GetComponent<Nigozi::TransformComponent>().Scale = glm::vec3(6.0f, 3.0f, 1.0f);

	Nigozi::Entity mainMenu = CreateEntity("Main", "MainMenuManager");
	mainMenu.AddComponent<Nigozi::ScriptComponent>(std::make_shared<MainMenuScript>(mainMenu));
}

MainMenuScene::~MainMenuScene()
{
}
