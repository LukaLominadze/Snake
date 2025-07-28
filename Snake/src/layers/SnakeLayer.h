#pragma once

#include <Nigozi.h>

class SnakeLayer : public Nigozi::Layer
{
public:
	SnakeLayer();
	~SnakeLayer() = default;

	virtual void OnAttach() override;
	virtual void OnEvent(Nigozi::Event& event) override;
	virtual void OnUpdate(float timestep) override;
	virtual void OnRender() override;
	virtual void OnImGuiRender() override;
private:
	bool OnWindowResized(Nigozi::WindowResizedEvent& event);
	bool OnKeyPressed(Nigozi::KeyPressedEvent& event);
private:
	float m_zoom = 6.0f;
	Nigozi::OrthographicCamera m_camera;
	Nigozi::SceneManager m_sceneManager;
};

