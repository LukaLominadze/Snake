#pragma once

#include <Nigozi.h>
#include "misc/Event.h"
#include "misc/Observer.h"

class ButtonScript : public Nigozi::Script
{
public:
	ButtonScript(Nigozi::Entity entity);
	~ButtonScript();

	virtual void OnEvent(Nigozi::Event& event) override;

	void AddOnStartedPressingListener(Observer* listener);
	void AddOnPressedListener(Observer* listener);
	void RemoveOnStartedPressingListener(Observer* listener);
	void RemoveOnPressedListener(Observer* listener);
private:
	bool OnMouseButtonPressedEvent(Nigozi::MouseButtonPressedEvent& event);
	bool OnMouseButtonReleasedEvent(Nigozi::MouseButtonReleasedEvent& event);
private:
	Event m_onStartedPressing, m_onPressed;
	Observer m_onStartedPressingListener, m_onPressedListener;

	glm::vec4 m_onPressingColor = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	glm::vec4 m_defaultColor = glm::vec4(1.0f);


	bool m_isPressing = false;
};

