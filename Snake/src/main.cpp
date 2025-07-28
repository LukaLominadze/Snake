#define MAIN

#include <Nigozi.h>
#include "SnakeApplication.h"

Nigozi::Application* CreateApplication() {
	Nigozi::Application* app = new SnakeApplication({ "Snake", 1600, 900, true, false, "logo-small.png" });
	return app;
}