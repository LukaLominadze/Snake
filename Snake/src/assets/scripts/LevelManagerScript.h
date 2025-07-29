#pragma once

#include <Nigozi.h>
#include "misc/Event.h"

class LevelManagerScript : public Nigozi::Script
{
public:
	LevelManagerScript(Nigozi::Entity entity);
	~LevelManagerScript();

	virtual void OnUpdate(float timestep) override;

	void AddScore();

	void AddListener(Observer* listener);
	void RemoveListener(Observer* listener);
private:
	Nigozi::Entity m_scoreDigit1Entity;
	Nigozi::Entity m_scoreDigit2Entity;

	Event m_event;

	std::shared_ptr<Nigozi::Texture> p_numberAtlas;
	std::shared_ptr<Nigozi::SubTexture> p_scoreDigit1SubTexture;
	std::shared_ptr<Nigozi::SubTexture> p_scoreDigit2SubTexture;

	float m_stepTime = 0.25f;
	float m_elapsedTime = 0.0f;
};

