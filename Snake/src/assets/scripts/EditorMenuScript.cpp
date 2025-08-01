#include "EditorMenuScript.h"

#include "misc/NFDUtils.h"
#include "yaml-cpp/yaml.h"

#include "ButtonScript.h"

EditorMenuScript::EditorMenuScript(Nigozi::Entity entity)
	:Script(entity),
	m_onLoadPressed([this]() {
		std::filesystem::path filePath = NFDUtils::OpenFileDialog("yaml");
		if (!filePath.empty()) {
			YAML::Emitter out;
			{
				out << YAML::BeginMap;
				out << YAML::Key << "CurrentLevel" << YAML::Value << filePath.string();
				out << YAML::EndMap;
			}

			{
				std::ofstream fout("src/assets/editor/editorCache.yaml");
				fout << out.c_str();
			}

			m_entityHandle.GetScene()->GetSceneManager()->QueueLoadScene("Editor");
		}
	}),
	m_onNewPressed([this]() {
		YAML::Emitter out;
		{
			out << YAML::BeginMap;
			out << YAML::Key << "CurrentLevel" << YAML::Value << "NONE";
			out << YAML::EndMap;
		}

		{
			std::ofstream fout("src/assets/editor/editorCache.yaml");
			fout << out.c_str();
		}

		m_entityHandle.GetScene()->GetSceneManager()->QueueLoadScene("Editor");
	}),
	m_onBackPressed([this]() {
		m_entityHandle.GetScene()->GetSceneManager()->QueueLoadScene("MainMenu");
	})
{
	Nigozi::Entity loadEntity = m_entityHandle.GetScene()->TryGetEntityByTag("LoadButton");
	Nigozi::Entity newEntity = m_entityHandle.GetScene()->TryGetEntityByTag("NewButton");
	Nigozi::Entity backEntity = m_entityHandle.GetScene()->TryGetEntityByTag("BackButton");

	auto& loadScript = loadEntity.GetComponent<Nigozi::ScriptComponent>();
	auto& newScript = newEntity.GetComponent<Nigozi::ScriptComponent>();
	auto& backScript = backEntity.GetComponent<Nigozi::ScriptComponent>();

	((ButtonScript*)(loadScript.ScriptHandle.get()))->AddOnPressedListener(&m_onLoadPressed);
	((ButtonScript*)(newScript.ScriptHandle.get()))->AddOnPressedListener(&m_onNewPressed);
	((ButtonScript*)(backScript.ScriptHandle.get()))->AddOnPressedListener(&m_onBackPressed);
}

EditorMenuScript::~EditorMenuScript()
{
}
