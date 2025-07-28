#include "SampleScene.h"
#include "assets/scripts/PlayerScript.h"

SampleScene::SampleScene()
{
	Nigozi::Entity player = CreateEntity("Player", "Player");
	player.AddComponent<Nigozi::SpriteRendererComponent>("src/Nigozi/res/textures/flatQuad.png", glm::vec2{ 0, 0 });
	player.AddComponent<Nigozi::ScriptComponent>(std::make_shared<PlayerScript>(player));
}

SampleScene::~SampleScene()
{
}
