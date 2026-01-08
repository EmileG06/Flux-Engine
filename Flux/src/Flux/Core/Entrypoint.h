#pragma once

#include "Flux/Core.h"

#ifdef FX_BUILD_APP
extern Flux::Application* Flux::CreateApplication();

int main(int argc, char** argv)
{
	Flux::Application* app = Flux::CreateApplication();
	app->Run();
	delete app;
}
#endif
