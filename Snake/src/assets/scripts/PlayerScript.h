#pragma once

#include <Nigozi.h>

class PlayerScript : public Nigozi::Script
{
public:
	PlayerScript(Nigozi::Entity entity);

	virtual void OnUpdate(float timestep) override;
private:
	float m_speed = 0.1f;
};

