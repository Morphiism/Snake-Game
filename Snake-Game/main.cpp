#include "SnakeGame.h"

int main()
{
	int classicMode;
	int speedMode;
	int speed = 200;
	int foodNum = 1;
	int poisonNum = 0;
	int wallNum = 0;
	int randomWalkMode;
	bool randomWalk = false;
	int maxIteration = 0;
	std::cout << "是否玩经典贪吃蛇？1. 否 2. 是" << std::endl;
	std::cin >> classicMode;
	if (classicMode == 1)
	{
		std::cout << "请选择游戏难度：1. 简单(x1) 2. 中等(x2) 3. 困难(x4)" << std::endl;
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
		std::cout << "请输入食物数量：(-0.02x每单位)" << std::endl;
		std::cin >> foodNum;
		if (foodNum <= 0)
		{
			std::cout << "不支持的输入，食物数量默认为1" << std::endl;
			foodNum = 1;
		}
		std::cout << "请输入毒药数量：(+0.1x每单位)" << std::endl;
		std::cin >> poisonNum;
		if (poisonNum < 0)
		{
			std::cout << "不支持的输入，毒药数量默认为0" << std::endl;
			poisonNum = 0;
		}
		std::cout << "请输入障碍物数量：(+0.2x每单位)" << std::endl;
		std::cin >> wallNum;
		if (wallNum < 0)
		{
			std::cout << "不支持的输入，障碍物数量默认为0" << std::endl;
			wallNum = 0;
		}
		std::cout << "是否开启随机游走？1. 否(x1) 2. 是(x5)" << std::endl;
		std::cin >> randomWalkMode;
		switch (randomWalkMode)
		{
		case 1:
			randomWalk = false;
			break;
		case 2:
			randomWalk = true;
			break;
		default:
			std::cout << "不支持的输入，随机游走默认关闭" << std::endl;
			randomWalk = false;
			break;
		}
		std::cout << "请输入最大迭代次数：(0为无限)" << std::endl;
		std::cin >> maxIteration;
		if (maxIteration < 0)
		{
			std::cout << "不支持的输入，最大迭代次数默认为0" << std::endl;
			maxIteration = 0;
		}
	}
	std::cout << "设置成功，即将进入游戏..." << std::endl;
	Sleep(1000);
	
	while (true)
	{
		SetConsoleTitle(TEXT("贪吃蛇"));
		Game game(speed, foodNum, poisonNum, wallNum, randomWalk, maxIteration);
		game.gaming();
	}

	return 0;
}