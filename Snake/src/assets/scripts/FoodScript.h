#pragma once

#include <Nigozi.h>

class FoodScript : public Nigozi::Script
{
public:
	FoodScript(Nigozi::Entity entity);

	void Eat();
};

