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

	std::shared_ptr<Nigozi::Texture> m_tailTexture;
	std::shared_ptr<Nigozi::SubTexture> m_tailSubTexture;

	std::vector<Nigozi::TransformComponent*> m_tail;

	// x = -1 <> 1
	// y = -2 <> 2
	std::unordered_map<float, float> m_headRotations = {
		{ 1.0f, 90.0f },
		{ -2.0f, 180.0f },
		{ -1.0f, 270.0f },
		{ 2.0f, 0.0f }
	};

	glm::vec4 m_color = glm::vec4(0.2f, 0.8f, 0.2f, 1.0f);
	glm::vec3 m_direction;
	float m_speed = 1.0f;
};

