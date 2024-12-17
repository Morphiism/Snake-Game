#include "SnakeGame.h"

void Game::init()
{
	SetConsoleTitle(TEXT("���������ʼ��Ϸ"));
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
	COORD coord;
	coord.X = HEIGHT + 2;
	coord.Y = WIDTH / 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "��WASD���Ʒ���";
	coord.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "��ǰ���ȣ�" << snake.getLength();
	std::ifstream file("highest.dat");
	int highest;
	file >> highest;
	file.close();
	coord.Y = 3;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "��󳤶ȣ�" << highest;
}

void Game::gaming()
{
	init();
	waitKey();
	getKey();
	SetConsoleTitle(TEXT("̰���ߣ���ESC��������Ϸ��"));
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

	int length = snake.getLength();
	COORD coord;
	coord.X = HEIGHT + 2;
	coord.Y = WIDTH - 4;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "��Ϸ�������������ճ���Ϊ��" << length;
	SetConsoleTitle(TEXT("����������¿�ʼ"));
	std::ifstream file("highest.dat");
	int highest;
	file >> highest;
	file.close();
	if (length > highest)
	{
		coord.Y = WIDTH - 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		std::cout << "�¼�¼��";
		std::ofstream file("highest.dat");
		file << length;
		file.close();
	}
	waitKey();
}