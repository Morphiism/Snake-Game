#include "SnakeGame.h"

void Game::init()
{
	SetConsoleTitle(TEXT("按任意键开始游戏"));
	grid = Grid();
	snake = Snake(Point(WIDTH / 2, HEIGHT / 2));
	key = 0;
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
	grid.update(snake);
	key = 0;
}

void Game::print() const
{
	system("cls");
	grid.print();
	pointat(HEIGHT + 2, WIDTH / 2);
	std::cout << "按WASD控制方向";
	pointat(HEIGHT + 2, 1);
	std::cout << "当前长度：" << snake.getLength();
	std::ifstream file("highest.dat");
	int highest;
	file >> highest;
	highest = max(highest, 1);
	file.close();
	pointat(HEIGHT + 2, 3);
	std::cout << "最大长度：" << highest;
}

void Game::gaming()
{
	init();
	waitKey();
	getKey();
	SetConsoleTitle(TEXT("贪吃蛇（按ESC键结束游戏）"));
	grid.generateFood(2);

	while (!snake.isDead())
	{
		Sleep(200);
		getKey();
		if (key == 27)
			break;
		update();
		print();
	}

	int length = snake.getLength();
	pointat(HEIGHT + 2, WIDTH / 2 + 2);
	std::cout << "游戏结束！您的最终长度为：" << length;
	SetConsoleTitle(TEXT("按任意键重新开始"));
	std::ifstream file("highest.dat");
	int highest;
	file >> highest;
	highest = max(highest, 1);
	file.close();
	if (length > highest)
	{
		pointat(HEIGHT + 2, WIDTH / 2 + 4);
		std::cout << "新纪录！";
		std::ofstream file("highest.dat");
		file << length;
		file.close();
	}
	waitKey();
}