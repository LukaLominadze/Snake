#include "SampleScene.h"
#include "assets/scripts/PlayerScript.h"
#include "assets/scripts/LevelManagerScript.h"
#include "assets/scripts/FoodScript.h"

SampleScene::SampleScene(Nigozi::SceneManager* sceneManager)
	:Scene(sceneManager)
{
	Nigozi::Entity levelManager = CreateEntity("LevelManager", "LevelManager");
	levelManager.AddComponent<Nigozi::ScriptComponent>(std::make_shared<LevelManagerScript>(levelManager));

	Nigozi::Entity player = CreateEntity("Player", "Player");
	player.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/snake-head.png", glm::vec2{ 0, 0 });
	player.AddComponent<Nigozi::ScriptComponent>(std::make_shared<PlayerScript>(player));

	Nigozi::Entity food = CreateEntity("Apple", "Food");
	food.AddComponent<Nigozi::SpriteRendererComponent>("src/assets/sprites/snake-tail.png", glm::vec2{ 0, 0 });
	food.AddComponent<Nigozi::ScriptComponent>(std::make_shared<FoodScript>(food));

	Nigozi::Renderer2D::SetClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

SampleScene::~SampleScene()
{
}
