#include "PlayerScript.h"
#include "StepTimerScript.h"

PlayerScript::PlayerScript(Nigozi::Entity entity)
	:Script(entity),
	m_onUpdate([this]() {
		auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
		transform.Position += glm::vec3(m_direction.x, m_direction.y, 0.0f);
		})
{
	m_direction = glm::vec3(1.0f, 0.0f, 0.0f);
	Nigozi::Entity stepTimer = m_entityHandle.GetScene()->TryGetEntityByTag("StepTimer");
	auto& script = stepTimer.GetComponent<Nigozi::ScriptComponent>().ScriptHandle;
	((StepTimerScript*)(script.get()))->AddListener(&m_onUpdate);
}

void PlayerScript::OnUpdate(float timestep)
{
	float directionX = Nigozi::Input::GetAxis(GLFW_KEY_A, GLFW_KEY_D);
	float directionY = Nigozi::Input::GetAxis(GLFW_KEY_S, GLFW_KEY_W);
	if (directionX != 0)
	{
		m_direction.x = directionX;
		m_direction.y = 0.0f;
	}
	else if (directionY != 0)
	{
		m_direction.y = directionY;
		m_direction.x = 0.0f;
	}
}
