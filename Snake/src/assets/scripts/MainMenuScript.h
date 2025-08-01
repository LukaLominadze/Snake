#pragma once

#include <Nigozi.h>
#include "misc/Observer.h"

class MainMenuScript : public Nigozi::Script
{
public:
	MainMenuScript(Nigozi::Entity entity);
	~MainMenuScript();
private:
	Observer m_onPlayPressed, m_onEditorPressed;
};

