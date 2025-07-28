#include "StepTimerScript.h"

StepTimerScript::StepTimerScript(Nigozi::Entity entity)
	:Script(entity)
{
}

StepTimerScript::~StepTimerScript()
{
}

void StepTimerScript::OnUpdate(float timestep)
{
	m_elapsedTime += timestep;
	if (m_elapsedTime >= m_stepTime) {
		m_event.Invoke();
		m_elapsedTime = 0.0f;
	}
}

void StepTimerScript::AddListener(Observer* listener)
{
	m_event.AddListener(listener);
}

void StepTimerScript::RemoveListener(Observer* listener)
{
	m_event.RemoveListener(listener);
}
