#include "SnakeGame.h"

Game::Game()
{
	grid = Grid();
	snake = Snake(Point(WIDTH / 2, HEIGHT / 2));
	key = 0;
}

void Game::init()
{
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
	if (key == 'w')
		snake.changeDir(Point(-1, 0));
	else if (key == 's')
		snake.changeDir(Point(1, 0));
	else if (key == 'a')
		snake.changeDir(Point(0, -1));
	else if (key == 'd')
		snake.changeDir(Point(0, 1));
	snake.move();
	grid.update(snake);
	key = 0;
}

void Game::print() const
{
	system("cls");
	COORD coord;
	coord.X = HEIGHT + 2;
	coord.Y = WIDTH / 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "��WASD���Ʒ��򣬰�ESC�˳�";
	coord.Y = WIDTH / 2 + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "��ǰ���ȣ�" << snake.getLength();
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	grid.print();
}

void Game::gaming()
{
	init();
	waitKey();
	grid.generateFood();

	while (!snake.isDead())
	{
		Sleep(200);
		getKey();
		if (key == 27)
			break;
		update();
		print();
	}

	COORD coord;
	coord.X = HEIGHT + 2;
	coord.Y = WIDTH / 2 + 4;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "��Ϸ�����������������";
}