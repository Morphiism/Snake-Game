#include "SnakeGame.h"

void Game::init()
{
	SetConsoleTitle(TEXT("���������ʼ��Ϸ"));
	grid = Grid();
	snake = Snake(Point(WIDTH / 2, HEIGHT / 2), snake.getInitSpeed());
	key = 0;
	grid.generateFood(foodNum);
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
	std::cout << "��WASD���Ʒ���";
	pointat(HEIGHT + 2, 1);
	std::cout << "��ǰģʽ��";
	switch (snake.getInitSpeed())
	{
	case 200:
		std::cout << "�� ";
		break;
	case 100:
		std::cout << "�е� ";
		break;
	case 50:
		std::cout << "���� ";
		break;
	}
	std::cout << foodNum << "ʳ��";
	pointat(HEIGHT + 2, 3);
	std::cout << "��ǰ���ȣ�" << snake.getLength();
	std::ifstream file("highest.dat");
	int highest;
	file >> highest;
	highest = max(highest, 1);
	file.close();
	pointat(HEIGHT + 2, 5);
	std::cout << "��󳤶ȣ�" << highest;
	pointat(HEIGHT + 2, 7);
	std::cout << "��ǰ�ٶȣ�" << snake.getSpeed() << " ms/it";
}

void Game::gaming()
{
	init();
	waitKey();
	getKey();
	SetConsoleTitle(TEXT("̰���ߣ���ESC����ͣ��Ϸ��"));

	while (!snake.isDead())
	{
		Sleep(snake.getSpeed());
		getKey();
		if (key == 27)
		{
			SetConsoleTitle(TEXT("���������������ESC��������Ϸ"));
			waitKey();
			getKey();
			if (key == 27)
				break;
			SetConsoleTitle(TEXT("̰���ߣ���ESC����ͣ��Ϸ��"));
		}
		update();
		print();
	}

	int length = snake.getLength();
	pointat(HEIGHT + 2, WIDTH / 2 + 2);
	std::cout << "��Ϸ�������������ճ���Ϊ��" << length;
	SetConsoleTitle(TEXT("����������¿�ʼ"));
	std::ifstream file("highest.dat");
	int highest;
	file >> highest;
	highest = max(highest, 1);
	file.close();
	if (length > highest)
	{
		pointat(HEIGHT + 2, WIDTH / 2 + 4);
		std::cout << "�¼�¼��";
		std::ofstream file("highest.dat");
		file << length;
		file.close();
	}
	waitKey();
}