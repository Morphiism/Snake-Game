#include "SnakeGame.h"

int main()
{
	std::cout << "按任意键开始游戏";

	Game game;
	while (true)
	{
		game.gaming();
	}

	return 0;
}