#include "MainMenuScript.h"
#include "assets/scripts/ButtonScript.h"

MainMenuScript::MainMenuScript(Nigozi::Entity entity)
	:Script(entity),
	m_onPressed([this]() {
			m_entityHandle.GetScene()->GetSceneManager()->LoadScene("Sample");
		})
{
	Nigozi::Entity buttonEntity = m_entityHandle.GetScene()->TryGetEntityByTag("PlayButton");
	auto& buttonScript = buttonEntity.GetComponent<Nigozi::ScriptComponent>();
	((ButtonScript*)(buttonScript.ScriptHandle.get()))->AddOnPressedListener(&m_onPressed);
}

MainMenuScript::~MainMenuScript()
{
}
