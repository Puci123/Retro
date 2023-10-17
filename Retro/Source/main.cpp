#include "App.h"

int main()
{


    App application(1200, 800, "Retro");

	while (application.IsRunning())
	{
		application.Loop();
	}


}


