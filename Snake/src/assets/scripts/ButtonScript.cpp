#include "ButtonScript.h"
#include "layers/SnakeLayer.h"

ButtonScript::ButtonScript(Nigozi::Entity entity)
    :Script(entity)
{
}

ButtonScript::~ButtonScript()
{
}

void ButtonScript::OnEvent(Nigozi::Event& event)
{
    Nigozi::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Nigozi::MouseButtonPressedEvent>(std::bind(&ButtonScript::OnMouseButtonPressedEvent, this, std::placeholders::_1));
    dispatcher.Dispatch<Nigozi::MouseButtonReleasedEvent>(std::bind(&ButtonScript::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
}

void ButtonScript::AddOnStartedPressingListener(Observer* listener)
{
    m_onStartedPressing.AddListener(listener);
}

void ButtonScript::AddOnPressedListener(Observer* listener)
{
    m_onPressed.AddListener(listener);
}

void ButtonScript::RemoveOnStartedPressingListener(Observer* listener)
{
    m_onStartedPressing.RemoveListener(listener);
}

void ButtonScript::RemoveOnPressedListener(Observer* listener)
{
    m_onPressed.RemoveListener(listener);
}

bool ButtonScript::OnMouseButtonPressedEvent(Nigozi::MouseButtonPressedEvent& event)
{
    if (m_isPressing) {
        return false;
    }
    if (event.GetButton() == GLFW_MOUSE_BUTTON_1) {
        glm::vec2 cameraPosition = SnakeLayer::GetMainCamera().GetMousePositionWorldSpace();
        auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
        if (cameraPosition.x > (transform.Position.x - transform.Scale.x / 2.0f) &&
            cameraPosition.x < (transform.Position.x + transform.Scale.x / 2.0f) &&
            cameraPosition.y >(transform.Position.y - transform.Scale.y / 2.0f) &&
            cameraPosition.y < (transform.Position.y + transform.Scale.y / 2.0f)) 
        {
            m_isPressing = true;
            m_onStartedPressing.Invoke();
            LOG("Pressing...");
            return false;
        }
    }
    return false;
}

bool ButtonScript::OnMouseButtonReleasedEvent(Nigozi::MouseButtonReleasedEvent& event)
{
    if (!m_isPressing) {
        return false;
    }
    if (event.GetButton() == GLFW_MOUSE_BUTTON_1) {
        m_isPressing = false;
        glm::vec2 cameraPosition = SnakeLayer::GetMainCamera().GetMousePositionWorldSpace();
        auto& transform = m_entityHandle.GetComponent<Nigozi::TransformComponent>();
        if (cameraPosition.x > (transform.Position.x - transform.Scale.x / 2.0f) &&
            cameraPosition.x < (transform.Position.x + transform.Scale.x / 2.0f) &&
            cameraPosition.y >(transform.Position.y - transform.Scale.y / 2.0f) &&
            cameraPosition.y < (transform.Position.y + transform.Scale.y / 2.0f))
        {
            m_onPressed.Invoke();
            LOG("Pressed!");
            return false;
        }
    }
    return false;
}
