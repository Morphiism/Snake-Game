#include "SnakeGame.h"

int main()
{
	int speedMode;
	int speed;
	int foodNum;
	while (true)
	{
		system("cls");
		std::cout << "请选择游戏难度：1. 简单 2. 中等 3. 困难" << std::endl;
		std::cin >> speedMode;
		switch (speedMode)
		{
		case 1:
			speed = 200;
			break;
		case 2:
			speed = 100;
			break;
		case 3:
			speed = 50;
			break;
		default:
			std::cout << "不支持的输入，游戏难度默认为简单" << std::endl;
			speed = 200;
			break;
		}
		std::cout << "请输入食物数量：" << std::endl;
		std::cin >> foodNum;
		if (foodNum <= 0)
		{
			std::cout << "不支持的输入，食物数量默认为1" << std::endl;
			foodNum = 1;
		}
		std::cout << "设置成功，按任意键开始游戏" << std::endl;

		Game game(speed, foodNum);
		game.gaming();
	}

	return 0;
}