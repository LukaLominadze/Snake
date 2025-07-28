#pragma once

#include <Nigozi.h>
#include "misc/Observer.h"

class PlayerScript : public Nigozi::Script
{
public:
	PlayerScript(Nigozi::Entity entity);

	virtual void OnUpdate(float timestep) override;
private:
	Observer m_onUpdate;

	std::vector<Nigozi::TransformComponent*> m_tail;

	glm::vec3 m_direction;
	float m_speed = 1.0f;
};

