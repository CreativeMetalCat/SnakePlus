
#include <SDL.h>
#include <Game.h>

int main(int argc, char* args[])
{

	try
	{
		Game* game = new Game();
		game->Init();
		while (!game->needsToClose)
		{
			game->Update();
			game->Draw();
		}
		game->Close();
	}
	catch (std::exception e)
	{
		return -1;
	}
	return 0;
}