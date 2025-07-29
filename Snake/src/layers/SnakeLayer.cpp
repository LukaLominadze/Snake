#include "SnakeLayer.h"
#include "assets/scenes/MainMenuScene.h"
#include "assets/scenes/SampleScene.h"

// Kind of hacky, but I think it's fine for now
static Nigozi::OrthographicCamera* s_MainCamera = nullptr;

SnakeLayer::SnakeLayer()
	:m_camera(-(16.0f / 9.0f) * m_zoom, (16.0f / 9.0f) * m_zoom, -m_zoom, m_zoom)
{
	// There is a little offset at position 0, don't know why
	m_camera.SetPosition(glm::vec3(0.5f, 0.0f, 0.0f));
	s_MainCamera = &m_camera;
}

void SnakeLayer::OnAttach()
{
	m_sceneManager = Nigozi::SceneManager("Sample", [this]() { return std::make_shared<SampleScene>(&m_sceneManager); });
	m_sceneManager.OnAttach();
	m_sceneManager.AddSceneToMap("MainMenu", [this]() { return std::make_shared<MainMenuScene>(&m_sceneManager); });
	m_sceneManager.LoadScene("MainMenu");
}

void SnakeLayer::OnEvent(Nigozi::Event& event)
{
	Nigozi::EventDispatcher dispatcher = Nigozi::EventDispatcher(event);
	dispatcher.Dispatch<Nigozi::WindowResizedEvent>(std::bind(&SnakeLayer::OnWindowResized, this, std::placeholders::_1));
	dispatcher.Dispatch<Nigozi::KeyPressedEvent>(std::bind(&SnakeLayer::OnKeyPressed, this, std::placeholders::_1));
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

Nigozi::OrthographicCamera& SnakeLayer::GetMainCamera()
{
	return *s_MainCamera;
}

bool SnakeLayer::OnWindowResized(Nigozi::WindowResizedEvent& event)
{
	float width = event.GetWidth();
	float height = event.GetHeight();
	float aspectRatio = width / height;
	m_camera.SetProjection(-aspectRatio * m_zoom, aspectRatio * m_zoom, -m_zoom, m_zoom);
	return false;
}

bool SnakeLayer::OnKeyPressed(Nigozi::KeyPressedEvent& event)
{
	if (event.GetKeyCode() == GLFW_KEY_F11) {
		Nigozi::Window::SetGlobalFullscreen(!Nigozi::Window::IsGlobalFullscreen());
	}
	return false;
}
