#pragma once

#include <Nigozi.h>
#include "misc/Observer.h"

class FoodScript : public Nigozi::Script
{
public:
	FoodScript(Nigozi::Entity entity);

	void Teleport();
private:
	Observer m_onLevelLoaded;
};

