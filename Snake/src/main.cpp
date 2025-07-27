#define MAIN

#include <Nigozi.h>

Nigozi::Application* CreateApplication() {
	Nigozi::Application* app = new Nigozi::Application({ "Snake", 1600, 900, true, false, "logo-small.png" });
	return app;
}