#include "SnakeApplication.h"

SnakeApplication::SnakeApplication(const Nigozi::ApplicationProps& props)
	:Nigozi::Application(props)
{
	PushLayer(&m_snakeLayer);
}
