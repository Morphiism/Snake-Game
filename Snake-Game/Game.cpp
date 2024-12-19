#include "SnakeGame.h"

//创建新的控制台缓冲区
HANDLE hOutput = CreateConsoleScreenBuffer(
	GENERIC_WRITE,//定义进程可以往缓冲区写数据
	FILE_SHARE_WRITE,//定义缓冲区可共享写权限
	NULL,
	CONSOLE_TEXTMODE_BUFFER,
	NULL
);
HANDLE* houtpoint{ &hOutput };//显示指针
COORD coord = { 0,0 };
//双缓冲处理显示
DWORD bytes = 0;


void Game::init()
{
	SetConsoleTitle(TEXT("按任意键开始游戏"));
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
		WriteConsoleOutputCharacterA(*houtpoint, (char*)"当前模式：简单", 14, coord, &bytes);
		break;
	case 100:
		WriteConsoleOutputCharacterA(*houtpoint, (char*)"当前模式：中等", 14, coord, &bytes);
		break;
	case 50:
		WriteConsoleOutputCharacterA(*houtpoint, (char*)"当前模式：困难", 14, coord, &bytes);
		break;
	}

	coord.X += 15;
	char dest[100];
	sprintf(dest, "%d食物 %d毒药 %d障碍物 随机游走%s 最大迭代%d", foodNum, poisonNum, wallNum, randomWalk ? "开启" : "关闭", maxIteration);
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	coord.X = HEIGHT + 2;
	coord.Y = 3;
	sprintf(dest, "当前长度：%d 当前分数：%d (%.2fx)", snake.getLength(), (int)score, getMultiplier());
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	std::ifstream file("highest.dat");
	double highest;
	file >> highest;
	highest = max(highest, 0);
	file.close();

	coord.X = HEIGHT + 2;
	coord.Y = 5;
	sprintf(dest, "最高分：%d", (int)highest);
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	coord.X = HEIGHT + 2;
	coord.Y = 7;
	sprintf(dest, "当前速度：%d (ms/it)", snake.getSpeed());
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	coord.X = HEIGHT + 2;
	coord.Y = 9;
	sprintf(dest, "当前迭代：%d/%d", iteration, maxIteration);
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);

	//设置新的缓冲区为活动显示缓冲
	SetConsoleActiveScreenBuffer(*houtpoint);
}

void Game::gaming()
{
	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);


	init();

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hOutput, &bufferInfo);
	// 用空格字符填充整个缓冲区
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
	SetConsoleTitle(TEXT("按WASD控制，按ESC键暂停"));
	
	while (!snake.isDead())
	{
		if (maxIteration > 0 && iteration >= maxIteration)
			break;
		Sleep(snake.getSpeed());
		getKey();
		if (key == 27)
		{
			SetConsoleTitle(TEXT("按任意键继续，按ESC键结束"));
			coord.X = HEIGHT + 2;
			coord.Y = WIDTH - 2;
			WriteConsoleOutputCharacterA(*houtpoint, "游戏暂停中...", 13, coord, &bytes);
			waitKey();
			getKey();
			if (key == 27)
				break;
			WriteConsoleOutputCharacterA(*houtpoint, "              ", 13, coord, &bytes);
			SetConsoleTitle(TEXT("按WASD控制，按ESC键暂停"));
		}
		update();
		iteration++;
		print();
	}

	coord.X = HEIGHT + 2;
	coord.Y = WIDTH - 2;
	char dest[100];
	sprintf(dest, "游戏结束！您的分数为：%d", (int)score);
	WriteConsoleOutputCharacterA(*houtpoint, dest, strlen(dest), coord, &bytes);
	SetConsoleTitle(TEXT("按Enter键重新开始"));
	std::ifstream file("highest.dat");
	double highest;
	file >> highest;
	highest = max(highest, 0);
	file.close();
	if (score > highest)
	{
		coord.X += strlen(dest);
		WriteConsoleOutputCharacterA(*houtpoint, " 新纪录！", 9, coord, &bytes);
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