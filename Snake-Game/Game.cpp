#include "SnakeGame.h"

void Game::init()
{
	SetConsoleTitle(TEXT("���������ʼ��Ϸ"));
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
	std::cout << foodNum << "ʳ�� ";
	std::cout << potionNum << "��ҩ";
	pointat(HEIGHT + 2, 3);
	std::cout << "��ǰ���ȣ�" << snake.getLength()
		<< " ��ǰ������" << std::fixed << std::setprecision(0) << score;
	std::cout << std::setprecision(2) << " (" << getMultiplier() << "x)";
	std::ifstream file("highest.dat");
	double highest;
	file >> highest;
	highest = max(highest, 0);
	file.close();
	pointat(HEIGHT + 2, 5);
	std::cout << "��߷֣�" << std::fixed << std::setprecision(0) << highest;
	pointat(HEIGHT + 2, 7);
	std::cout << "��ǰ�ٶȣ�" << snake.getSpeed() << " (ms/it)";
}

void Game::gaming()
{
	init();
	waitKey();
	getKey();
	SetConsoleTitle(TEXT("��WASD���ƣ���ESC����ͣ"));

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

	pointat(HEIGHT + 2, WIDTH / 2);
	std::cout << "��Ϸ���������ķ���Ϊ��" << std::fixed << std::setprecision(0) << score;
	SetConsoleTitle(TEXT("��Enter�����¿�ʼ"));
	std::ifstream file("highest.dat");
	double highest;
	file >> highest;
	highest = max(highest, 0);
	file.close();
	if (score > highest)
	{
		std::cout << " �¼�¼��";
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