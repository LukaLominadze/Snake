#pragma once

#include <Nigozi.h>

#include "misc/Observer.h"

class EditorMenuScript : public Nigozi::Script
{
public:
	EditorMenuScript(Nigozi::Entity entity);
	~EditorMenuScript();
private:
	Observer m_onLoadPressed, m_onNewPressed, m_onBackPressed;
};

