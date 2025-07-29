#include "LevelManagerScript.h"

LevelManagerScript::LevelManagerScript(Nigozi::Entity entity)
	:Script(entity),
	p_numberAtlas(std::make_shared<Nigozi::Texture>("src/assets/sprites/numbers.png")),
	p_scoreDigit1SubTexture(std::make_shared<Nigozi::SubTexture>(p_numberAtlas, glm::vec2(128.0f, 128.0f), 1, 0)),
	p_scoreDigit2SubTexture(std::make_shared<Nigozi::SubTexture>(p_numberAtlas, glm::vec2(128.0f, 128.0f), 0, 0))
{
	m_scoreDigit1Entity = m_entityHandle.GetScene()->CreateEntity("Score0", "Score");
	m_scoreDigit1Entity.AddComponent<Nigozi::SpriteRendererComponent>(p_numberAtlas, p_scoreDigit1SubTexture);
	auto& transform1 = m_scoreDigit1Entity.GetComponent<Nigozi::TransformComponent>();
	transform1.Position.y = 5.5f;
	transform1.Position.x = 0.5f;

	m_scoreDigit2Entity = m_entityHandle.GetScene()->CreateEntity("Score1", "Score");
	m_scoreDigit2Entity.AddComponent<Nigozi::SpriteRendererComponent>(p_numberAtlas, p_scoreDigit2SubTexture);
	auto& transform2 = m_scoreDigit2Entity.GetComponent<Nigozi::TransformComponent>();
	transform2.Position.y = 5.5f;
	transform2.Position.x = 0.0f;
}

LevelManagerScript::~LevelManagerScript()
{
}

void LevelManagerScript::OnUpdate(float timestep)
{
	m_elapsedTime += timestep;
	if (m_elapsedTime >= m_stepTime) {
		m_event.Invoke();
		m_elapsedTime = 0.0f;
	}
}

void LevelManagerScript::AddScore()
{
	auto& sprite1 = m_scoreDigit1Entity.GetComponent<Nigozi::SpriteRendererComponent>();
	uint32_t slotX1 = sprite1.Sprite->GetSlotX();
	auto& sprite2 = m_scoreDigit2Entity.GetComponent<Nigozi::SpriteRendererComponent>();
	uint32_t slotX2 = sprite2.Sprite->GetSlotX();
	if (++slotX1 <= 10) {
		sprite1.Sprite->SetSlot(slotX1, 0);
	}
	else {
		if (slotX2 == 0)
			slotX2 = 1;
		sprite2.Sprite->SetSlot(++slotX2, 0);
		sprite1.Sprite->SetSlot(1, 0);
	}
}

void LevelManagerScript::AddListener(Observer* listener)
{
	m_event.AddListener(listener);
}

void LevelManagerScript::RemoveListener(Observer* listener)
{
	m_event.RemoveListener(listener);
}
