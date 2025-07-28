#include "PlayerScript.h"

PlayerScript::PlayerScript(Nigozi::Entity entity)
	:Script(entity)
{
}

void PlayerScript::OnUpdate(float timestep)
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
	float directionX = -(static_cast<float>(Nigozi::Input::IsKeyPressed(GLFW_KEY_A))) +
						(static_cast<float>(Nigozi::Input::IsKeyPressed(GLFW_KEY_D)));
	float directionY = -(static_cast<float>(Nigozi::Input::IsKeyPressed(GLFW_KEY_S))) +
						(static_cast<float>(Nigozi::Input::IsKeyPressed(GLFW_KEY_W)));
	transform.Position += glm::vec3(directionX * m_speed, directionY * m_speed, 0.0f);
}
