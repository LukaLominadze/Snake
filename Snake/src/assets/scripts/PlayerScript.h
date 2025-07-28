#pragma once

#include <Nigozi.h>

class PlayerScript : public Nigozi::Script
{
public:
	PlayerScript(Nigozi::Entity entity);

	virtual void OnUpdate(float timestep) override;
private:
	glm::vec3 direction;
	float m_speed = 4.0f;
};

