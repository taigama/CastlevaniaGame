#include <windows.h>
#include <stdlib.h>
#include "MainGame.h"


	/////////////////
	// Include:
	// d3d9.lib
	// d3dx9.lib
	// dinput8.lib
	// dxguid.lib
	// dsound.lib
	// dxerr.lib
	// winmm.lib
	/////////////////

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));
	MainGame thisGame(hInstance, "Castlevania", 0, 60);
	thisGame.Init();
	thisGame.Run();
	return 0;
}