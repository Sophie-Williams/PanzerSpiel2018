// DiePanzer.cpp : Definiert den Einstiegspunkt f�r die Anwendung.
//

#include "stdafx.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Game& game = Game::GetInstance();
	game.Setup();
	game.MainLoop();
}


