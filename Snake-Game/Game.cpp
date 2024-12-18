#include "SnakeGame.h"

void Game::init()
{
	SetConsoleTitle(TEXT("按任意键开始游戏"));
	grid = Grid();
	snake = Snake(Point(WIDTH / 2, HEIGHT / 2), snake.getInitSpeed());
	grid.generateFood(foodNum);
	grid.generatePotion(potionNum);
}

void Game::waitKey()
{
	while (!_kbhit())
		Sleep(100);
}

void Game::getKey()
{
	if (_kbhit())
	{
		key = _getch();
	}
}

void Game::update()
{
	if (key == 'w' && (snake.getLength() == 1 || snake.getDir() != Point(1, 0)))
		snake.changeDir(Point(-1, 0));
	else if (key == 's' && (snake.getLength() == 1 || snake.getDir() != Point(-1, 0)))
		snake.changeDir(Point(1, 0));
	else if (key == 'a' && (snake.getLength() == 1 || snake.getDir() != Point(0, 1)))
		snake.changeDir(Point(0, -1));
	else if (key == 'd' && (snake.getLength() == 1 || snake.getDir() != Point(0, -1)))
		snake.changeDir(Point(0, 1));
	snake.move();
	int length = snake.getLength();
	grid.update(snake);
	if (snake.getLength() > length)
	{
		score += 10 * getMultiplier();
	}
	key = 0;
}

void Game::print() const
{
	system("cls");
	grid.print();
	pointat(HEIGHT + 2, 1);
	std::cout << "当前模式：";
	switch (snake.getInitSpeed())
	{
	case 200:
		std::cout << "简单 ";
		break;
	case 100:
		std::cout << "中等 ";
		break;
	case 50:
		std::cout << "困难 ";
		break;
	}
	std::cout << foodNum << "食物 ";
	std::cout << potionNum << "毒药";
	pointat(HEIGHT + 2, 3);
	std::cout << "当前长度：" << snake.getLength()
		<< " 当前分数：" << std::fixed << std::setprecision(0) << score;
	std::cout << std::setprecision(2) << " (" << getMultiplier() << "x)";
	std::ifstream file("highest.dat");
	double highest;
	file >> highest;
	highest = max(highest, 0);
	file.close();
	pointat(HEIGHT + 2, 5);
	std::cout << "最高分：" << std::fixed << std::setprecision(0) << highest;
	pointat(HEIGHT + 2, 7);
	std::cout << "当前速度：" << snake.getSpeed() << " (ms/it)";
}

void Game::gaming()
{
	init();
	waitKey();
	getKey();
	SetConsoleTitle(TEXT("按WASD控制，按ESC键暂停"));

	while (!snake.isDead())
	{
		Sleep(snake.getSpeed());
		getKey();
		if (key == 27)
		{
			SetConsoleTitle(TEXT("按任意键继续，按ESC键结束游戏"));
			waitKey();
			getKey();
			if (key == 27)
				break;
			SetConsoleTitle(TEXT("贪吃蛇（按ESC键暂停游戏）"));
		}
		update();
		print();
	}

	pointat(HEIGHT + 2, WIDTH / 2);
	std::cout << "游戏结束！您的分数为：" << std::fixed << std::setprecision(0) << score;
	SetConsoleTitle(TEXT("按Enter键重新开始"));
	std::ifstream file("highest.dat");
	double highest;
	file >> highest;
	highest = max(highest, 0);
	file.close();
	if (score > highest)
	{
		std::cout << " 新纪录！";
		std::ofstream file("highest.dat");
		file << score;
		file.close();
	}
	while (key != 13)
	{
		waitKey();
		getKey();
	}
}