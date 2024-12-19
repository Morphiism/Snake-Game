#include "SnakeGame.h"

//�����µĿ���̨������
HANDLE hOutput = CreateConsoleScreenBuffer(
	GENERIC_WRITE,//������̿�����������д����
	FILE_SHARE_WRITE,//���建�����ɹ���дȨ��
	NULL,
	CONSOLE_TEXTMODE_BUFFER,
	NULL
);
HANDLE* houtpoint{ &hOutput };//��ʾָ��
COORD coord = { 0,0 };
//˫���崦����ʾ
DWORD bytes = 0;


void Game::init()
{
	SetConsoleTitle(TEXT("���������ʼ��Ϸ"));
	grid.generateFood(foodNum);
	grid.generatePotion(poisonNum);
	grid.generateWall(wallNum);
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
	if (randomWalk)
		grid.randomWalk();
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
	grid.print(houtpoint);
	coord.X = HEIGHT + 2;
	coord.Y = 1;
	switch (snake.getInitSpeed())
	{
	case 200:
		WriteConsoleOutputCharacterA(*houtpoint, (char*)"��ǰģʽ����", 14, coord, &bytes);
		break;
	case 100:
		WriteConsoleOutputCharacterA(*houtpoint, (char*)"��ǰģʽ���е�", 14, coord, &bytes);
		break;
	case 50:
		WriteConsoleOutputCharacterA(*houtpoint, (char*)"��ǰģʽ������", 14, coord, &bytes);
		break;
	}

	coord.X += 15;
	char dest[100];
	sprintf(dest, "%dʳ�� %d��ҩ %d�ϰ��� �������%s ������%d", foodNum, poisonNum, wallNum, randomWalk ? "����" : "�ر�", maxIteration);
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	coord.X = HEIGHT + 2;
	coord.Y = 3;
	sprintf(dest, "��ǰ���ȣ�%d ��ǰ������%d (%.2fx)", snake.getLength(), (int)score, getMultiplier());
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	std::ifstream file("highest.dat");
	double highest;
	file >> highest;
	highest = max(highest, 0);
	file.close();

	coord.X = HEIGHT + 2;
	coord.Y = 5;
	sprintf(dest, "��߷֣�%d", (int)highest);
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	coord.X = HEIGHT + 2;
	coord.Y = 7;
	sprintf(dest, "��ǰ�ٶȣ�%d (ms/it)", snake.getSpeed());
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	coord.X = HEIGHT + 2;
	coord.Y = 9;
	sprintf(dest, "��ǰ������%d/%d", iteration, maxIteration);
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	//�����µĻ�����Ϊ���ʾ����
	SetConsoleActiveScreenBuffer(*houtpoint);
}

void Game::gaming()
{
	//���������������Ĺ��
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);


	init();

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hOutput, &bufferInfo);
	// �ÿո��ַ��������������
	DWORD written;
	FillConsoleOutputCharacter(
		hOutput,
		' ',
		bufferInfo.dwSize.X * bufferInfo.dwSize.Y,
		{ 0, 0 },
		&written
	);

	waitKey();
	getKey();
	SetConsoleTitle(TEXT("��WASD���ƣ���ESC����ͣ"));
	
	while (!snake.isDead())
	{
		if (maxIteration > 0 && iteration >= maxIteration)
			break;
		Sleep(snake.getSpeed());
		getKey();
		if (key == 27)
		{
			SetConsoleTitle(TEXT("���������������ESC������"));
			coord.X = HEIGHT + 2;
			coord.Y = WIDTH - 2;
			WriteConsoleOutputCharacterA(*houtpoint, "��Ϸ��ͣ��...", 13, coord, &bytes);
			waitKey();
			getKey();
			if (key == 27)
				break;
			WriteConsoleOutputCharacterA(*houtpoint, "              ", 13, coord, &bytes);
			SetConsoleTitle(TEXT("��WASD���ƣ���ESC����ͣ"));
		}
		update();
		iteration++;
		print();
	}

	coord.X = HEIGHT + 2;
	coord.Y = WIDTH - 2;
	char dest[100];
	sprintf(dest, "��Ϸ���������ķ���Ϊ��%d", (int)score);
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);
	SetConsoleTitle(TEXT("��Enter�����¿�ʼ"));
	std::ifstream file("highest.dat");
	double highest;
	file >> highest;
	highest = max(highest, 0);
	file.close();
	if (score > highest)
	{
		coord.X += strlen(dest);
		WriteConsoleOutputCharacterA(*houtpoint, " �¼�¼��", 9, coord, &bytes);
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