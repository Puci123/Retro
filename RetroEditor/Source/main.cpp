#include "App.h"

int main()
{
	App app(2000, 1000, "Retro");

	while (app.IsRunning())
	{
		app.Loop();
	}

}


