#define MAIN

#include <Nigozi.h>
#include "SnakeApplication.h"

Nigozi::Application* CreateApplication() {
	Nigozi::ApplicationProps props;
	props.Title = "Snake";
	props.Width = 1600;
	props.Height = 900;
	props.VSync = false;
	props.Fullscreen = false;
	props.IconPath = "logo-small.png";
	Nigozi::Application* app = new SnakeApplication(props);
	return app;
}