#include "PlayerScript.h"
#include "LevelManagerScript.h"
#include "FoodScript.h"

PlayerScript::PlayerScript(Nigozi::Entity entity)
	:Script(entity),
	m_tailTexture(std::make_shared<Nigozi::Texture>("src/assets/sprites/snake-tail.png")),
	m_tailSubTexture(std::make_shared<Nigozi::SubTexture>(m_tailTexture, glm::vec2{ 0.0f, 0.0f })),
	m_onUpdate([this]() {
			if (TailCollisionAndMovement()) {
				EatFood();
			}
		}),
	m_onLevelLoaded([this]() {
			std::vector<Nigozi::Entity> tails = m_entityHandle.GetScene()->TryGetEntitiesByTag("Tail");
			for (Nigozi::Entity entity : tails) {
				entity.Destroy();
			}
			m_tail.clear();

			Nigozi::Entity levelManager = m_entityHandle.GetScene()->TryGetEntityByTag("LevelManager");
			auto& script = levelManager.GetComponent<Nigozi::ScriptComponent>().ScriptHandle;
			glm::vec2 spawnPosition = ((LevelManagerScript*)(script.get()))->GetPlayerSpawnPosition();

			auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
			transform.Position = spawnPosition;
			
			m_direction = glm::vec2(1.0f, 0.0f);
		})
{
	m_direction = glm::vec2(1.0f, 0.0f);

	auto& sprite = m_entityHandle.GetComponent<Nigozi::SpriteRendererComponent>();
	sprite.Color = m_color;

	Nigozi::Entity levelManager = m_entityHandle.GetScene()->TryGetEntityByTag("LevelManager");
	auto& script = levelManager.GetComponent<Nigozi::ScriptComponent>().ScriptHandle;
	((LevelManagerScript*)(script.get()))->AddOnStepListener(&m_onUpdate);
	((LevelManagerScript*)(script.get()))->AddOnLevelLoadedListener(&m_onLevelLoaded);
}

void PlayerScript::OnUpdate(float timestep)
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();

	float directionX = Nigozi::Input::GetAxis(GLFW_KEY_A, GLFW_KEY_D);
	float directionY = Nigozi::Input::GetAxis(GLFW_KEY_S, GLFW_KEY_W);
	if (directionX != 0 && m_direction.x != -directionX)
	{
		if (!m_tail.empty()) {
			glm::vec2 diff = glm::abs(m_tail[0]->Position - (transform.Position + glm::vec2(directionX, 0.0f)));
			if (diff.x >= 0.1f || diff.y >= 0.1f) {
				m_direction.x = directionX;
				m_direction.y = 0.0f;
			}
		}
		else {
			m_direction.x = directionX;
			m_direction.y = 0.0f;
		}
	}
	else if (directionY != 0 && m_direction.y != -directionY)
	{
		if (!m_tail.empty()) {
			glm::vec2 diff = glm::abs(m_tail[0]->Position - (transform.Position + glm::vec2(0.0f, directionY)));
			if (diff.x >= 0.1f || diff.y >= 0.1f) {
				m_direction.y = directionY;
				m_direction.x = 0.0f;
			}
		}
		else {
			m_direction.y = directionY;
			m_direction.x = 0.0f;
		}
	}
}

bool PlayerScript::TailCollisionAndMovement()
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();

	if (!m_tail.empty()) {
		for (auto* position : m_tail) {
			glm::vec2 diff = glm::abs(transform.Position - position->Position);
			if (diff.x < 0.1f && diff.y < 0.1f) {
				m_entityHandle.GetScene()->GetSceneManager()->LoadCurrentScene();
				return false;
			}
		}
		for (size_t i = m_tail.size() - 1; i > 0; i--) {
			m_tail[i]->Position = m_tail[i - 1]->Position;
		}
		m_tail[0]->Position = transform.Position;
	}

	transform.Position += glm::vec2(m_direction.x * m_speed, m_direction.y * m_speed);
	// Head rotation
	transform.Rotation = m_direction.x * 90.0f +
		(m_direction.y + 3) * m_direction.y * 90.0f;
	return true;
}

void PlayerScript::EatFood()
{
	auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
	std::vector<Nigozi::Entity> foods = m_entityHandle.GetScene()->TryGetEntitiesByTag("Food");
	if (foods.empty()) {
		return;
	}
	for (Nigozi::Entity& food : foods) {
		auto& foodTransform = food.GetComponent<Nigozi::TransformComponent>();
		glm::vec2 diff = glm::abs(transform.Position - foodTransform.Position);
		if (diff.x < 0.1f && diff.y < 0.1f) {
			Nigozi::Entity tail = m_entityHandle.GetScene()->CreateEntity("Tail" + m_tail.size(), "Tail");
			auto& sprite = tail.AddComponent<Nigozi::SpriteRendererComponent>(m_tailTexture, m_tailSubTexture);
			if (m_tail.size() < 20) {
				sprite.Color = glm::vec4(m_color.x + m_tail.size() * 0.05f, m_color.y, m_color.z, m_color.w);
			}
			else {
				sprite.Color = glm::vec4(1.0f - (m_tail.size() - 20) * 0.05f, m_color.y, m_color.z + (m_tail.size() - 20) * 0.05f, m_color.w);
			}
			auto& tailTransform = tail.GetComponent<Nigozi::TransformComponent>();
			if (m_tail.empty()) {
				tailTransform.Position = transform.Position - glm::vec2(m_direction.x * m_speed, m_direction.y * m_speed);
			}
			else if (m_tail.size() == 1) {
				tailTransform.Position = m_tail[0]->Position - glm::vec2(m_direction.x * m_speed, m_direction.y * m_speed);
			}
			else {
				glm::vec2 diff = m_tail[m_tail.size() - 1]->Position - m_tail[m_tail.size() - 2]->Position;
				glm::vec2 direction = glm::sign(diff);
				tailTransform.Position = m_tail[m_tail.size() - 1]->Position + direction * m_speed;
			}
			m_tail.push_back(&tailTransform);
			auto& script = food.GetComponent<Nigozi::ScriptComponent>();
			((FoodScript*)(script.ScriptHandle.get()))->Teleport();
			Nigozi::Entity levelManager = m_entityHandle.GetScene()->TryGetEntityByTag("LevelManager");
			auto& levelManagerScript = levelManager.GetComponent<Nigozi::ScriptComponent>();
			((LevelManagerScript*)(levelManagerScript.ScriptHandle.get()))->AddScore();
			break;
		}
	}
}
