#include "SnakeLayer.h"
#include "assets/scenes/MainMenuScene.h"
#include "assets/scenes/SampleScene.h"

SnakeLayer::SnakeLayer()
	:m_camera(-(16.0f / 9.0f) * m_zoom, (16.0f / 9.0f) * m_zoom, -m_zoom, m_zoom)
{
}

void SnakeLayer::OnAttach()
{
	m_sceneManager = Nigozi::SceneManager("Sample", [this]() { return std::make_shared<SampleScene>(&m_sceneManager); });
	m_sceneManager.OnAttach();
	m_sceneManager.AddSceneToMap("MainMenu", [this]() { return std::make_shared<MainMenuScene>(&m_sceneManager); });
	m_sceneManager.LoadScene("Sample");
}

void SnakeLayer::OnEvent(Nigozi::Event& event)
{
	Nigozi::EventDispatcher dispatcher = Nigozi::EventDispatcher(event);
	dispatcher.Dispatch<Nigozi::WindowResizedEvent>(std::bind(&SnakeLayer::OnWindowResized, this, std::placeholders::_1));
	m_sceneManager.OnEvent(event);
}

void SnakeLayer::OnUpdate(float timestep)
{
	m_sceneManager.OnUpdate(timestep);
}

void SnakeLayer::OnRender()
{
	m_camera.SetMVPMatrix();
	m_sceneManager.OnRender();
}

void SnakeLayer::OnImGuiRender()
{
	m_sceneManager.OnImGuiRender();
}

bool SnakeLayer::OnWindowResized(Nigozi::WindowResizedEvent& event)
{
	float width = event.GetWidth();
	float height = event.GetHeight();
	float aspectRatio = width / height;
	m_camera.SetProjection(-aspectRatio * m_zoom, aspectRatio * m_zoom, -m_zoom, m_zoom);
	return false;
}
