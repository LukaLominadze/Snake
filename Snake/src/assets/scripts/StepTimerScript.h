#pragma once

#include <Nigozi.h>
#include "Event.h"

class StepTimerScript : public Nigozi::Script
{
public:
	StepTimerScript(Nigozi::Entity entity);
	~StepTimerScript();

	virtual void OnUpdate(float timestep) override;

	void AddListener(Observer* listener);
	void RemoveListener(Observer* listener);
private:
	Event m_event;

	float m_stepTime = 0.5f;
	float m_elapsedTime = 0.0f;
};

