//DEBUG CODE
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Game.h"
#include <time.h>

int main()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	std::unique_ptr<Game> game(new Game());
	srand(time(NULL));
	game->Run();

	return EXIT_SUCCESS;
}