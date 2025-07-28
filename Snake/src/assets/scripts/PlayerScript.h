#pragma once

#include <Nigozi.h>
#include "Observer.h"

class PlayerScript : public Nigozi::Script
{
public:
	PlayerScript(Nigozi::Entity entity);

	virtual void OnUpdate(float timestep) override;
private:
	Observer m_onUpdate;

	glm::vec3 m_direction;
	float m_speed = 4.0f;
};

