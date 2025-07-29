#pragma once

#include <Nigozi.h>
#include "misc/Observer.h"

class PlayerScript : public Nigozi::Script
{
public:
	PlayerScript(Nigozi::Entity entity);

	virtual void OnUpdate(float timestep) override;
private:
	bool TailCollisionAndMovement();
	void EatFood();
private:
	Observer m_onUpdate, m_onLevelLoaded;

	std::shared_ptr<Nigozi::Texture> m_tailTexture;
	std::shared_ptr<Nigozi::SubTexture> m_tailSubTexture;

	std::vector<Nigozi::TransformComponent*> m_tail;

	glm::vec4 m_color = glm::vec4(0.2f, 0.8f, 0.2f, 1.0f);
	glm::vec2 m_direction;
	float m_speed = 1.0f;
};

