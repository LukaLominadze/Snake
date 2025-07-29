#include "FoodScript.h"
#include <random>
#include "LevelManagerScript.h"

FoodScript::FoodScript(Nigozi::Entity entity)
	:Script(entity),
	m_onLevelLoaded([this]() {
			Teleport();
		})
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
	
	Nigozi::Entity levelManager = m_entityHandle.GetScene()->TryGetEntityByTag("LevelManager");
	auto& script = levelManager.GetComponent<Nigozi::ScriptComponent>();
	
	const std::vector<glm::vec2>& positions = ((LevelManagerScript*)(script.ScriptHandle.get()))->GetFloorPositions();
	std::random_device rd;
	
	std::uniform_int_distribution<size_t> dist(0, positions.size() - 1);
	size_t it = dist(rd);
	LOG("At! " << it);
	transform.Position = positions.at(it);
	transform.Scale = glm::vec2(0.5f, 0.5f);

	auto& sprite = m_entityHandle.GetComponent<Nigozi::SpriteRendererComponent>();
	sprite.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	((LevelManagerScript*)(script.ScriptHandle.get()))->AddOnLevelLoadedListener(&m_onLevelLoaded);
}

void FoodScript::Teleport()
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();

	Nigozi::Entity levelManager = m_entityHandle.GetScene()->TryGetEntityByTag("LevelManager");
	auto& script = levelManager.GetComponent<Nigozi::ScriptComponent>();

	const std::vector<glm::vec2>& positions = ((LevelManagerScript*)(script.ScriptHandle.get()))->GetFloorPositions();
	std::random_device rd;

	std::uniform_int_distribution<size_t> dist(0, positions.size());
	size_t it = dist(rd);
	LOG("At! " << it);
	transform.Position = positions.at(it);
	transform.Scale = glm::vec2(0.5f, 0.5f);
}
