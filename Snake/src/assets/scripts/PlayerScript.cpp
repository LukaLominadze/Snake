#include "PlayerScript.h"

PlayerScript::PlayerScript(Nigozi::Entity entity)
	:Script(entity)
{
	direction = glm::vec3(1.0f, 0.0f, 0.0f);
}

void PlayerScript::OnUpdate(float timestep)
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
	float directionX = Nigozi::Input::GetAxis(GLFW_KEY_A, GLFW_KEY_D);
	float directionY = Nigozi::Input::GetAxis(GLFW_KEY_S, GLFW_KEY_W);
	if (directionX != 0)
	{
		direction.x = directionX;
		direction.y = 0.0f;
	}
	else if (directionY != 0)
	{
		direction.y = directionY;
		direction.x = 0.0f;
	}
	transform.Position += glm::vec3(direction.x * m_speed * timestep, direction.y * m_speed * timestep, 0.0f);
}
