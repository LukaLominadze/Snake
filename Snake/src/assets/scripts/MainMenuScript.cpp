#include "MainMenuScript.h"
#include "assets/scripts/ButtonScript.h"

MainMenuScript::MainMenuScript(Nigozi::Entity entity)
	:Script(entity),
	m_onPlayPressed([this]() {
			m_entityHandle.GetScene()->GetSceneManager()->QueueLoadScene("Game");
		}),
	m_onEditorPressed([this]() {
			m_entityHandle.GetScene()->GetSceneManager()->QueueLoadScene("EditorMenu");
		})
{
	Nigozi::Entity buttonEntity = m_entityHandle.GetScene()->TryGetEntityByTag("PlayButton");
	auto& buttonScript = buttonEntity.GetComponent<Nigozi::ScriptComponent>();
	((ButtonScript*)(buttonScript.ScriptHandle.get()))->AddOnPressedListener(&m_onPlayPressed);

	Nigozi::Entity editorEntity = m_entityHandle.GetScene()->TryGetEntityByTag("EditorButton");
	auto& editorScript = editorEntity.GetComponent<Nigozi::ScriptComponent>();
	((ButtonScript*)(editorScript.ScriptHandle.get()))->AddOnPressedListener(&m_onEditorPressed);
}

MainMenuScript::~MainMenuScript()
{
}
