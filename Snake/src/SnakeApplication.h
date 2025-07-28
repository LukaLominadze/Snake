#pragma once

#include <Nigozi.h>
#include "layers/SnakeLayer.h"

class SnakeApplication : public Nigozi::Application
{
public:
	SnakeApplication(const Nigozi::ApplicationProps& props);
private:
	
	SnakeLayer m_snakeLayer;
};

