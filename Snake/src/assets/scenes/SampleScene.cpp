#include "SampleScene.h"
#include "assets/scripts/PlayerScript.h"
#include "assets/scripts/StepTimerScript.h"
#include "assets/scripts/FoodScript.h"

SampleScene::SampleScene()
{
	Nigozi::Entity stepTimer = CreateEntity("StepTimer", "StepTimer");
	stepTimer.AddComponent<Nigozi::ScriptComponent>(std::make_shared<StepTimerScript>(stepTimer));

	Nigozi::Entity player = CreateEntity("Player", "Player");
	player.AddComponent<Nigozi::SpriteRendererComponent>("src/Nigozi/res/textures/flatQuad.png", glm::vec2{ 0, 0 });
	player.AddComponent<Nigozi::ScriptComponent>(std::make_shared<PlayerScript>(player));

	Nigozi::Entity food = CreateEntity("Apple", "Food");
	food.AddComponent<Nigozi::SpriteRendererComponent>("src/Nigozi/res/textures/flatQuad.png", glm::vec2{ 0, 0 });
	food.AddComponent<Nigozi::ScriptComponent>(std::make_shared<FoodScript>(food));
}

SampleScene::~SampleScene()
{
}
