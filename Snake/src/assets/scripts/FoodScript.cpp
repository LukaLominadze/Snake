#include "FoodScript.h"
#include <random>

FoodScript::FoodScript(Nigozi::Entity entity)
	:Script(entity)
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
	std::random_device rd;
	std::uniform_int_distribution<int> distX(-4, 4);
	std::uniform_int_distribution<int> distY(-4, 4);
	transform.Position.x = distX(rd);
	transform.Position.y = distY(rd);
	transform.Scale = glm::vec3(0.5f, 0.5f, 1.0f);

	auto& sprite = m_entityHandle.GetComponent<Nigozi::SpriteRendererComponent>();
	sprite.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

void FoodScript::Eat()
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
	std::random_device rd;
	std::uniform_int_distribution<int> distX(-4, 4);
	std::uniform_int_distribution<int> distY(-4, 4);
	transform.Position.x = distX(rd);
	transform.Position.y = distY(rd);
}
