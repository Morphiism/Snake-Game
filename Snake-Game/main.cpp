#include "SnakeGame.h"

int main()
{
	int speedMode;
	int speed;
	int foodNum;
	int poisonNum;
	int wallNum;
	int randomWalkMode;
	bool randomWalk;
	while (true)
	{
		system("cls");
		SetConsoleTitle(TEXT("̰����"));
		std::cout << "��ѡ����Ϸ�Ѷȣ�1. ��(x1) 2. �е�(x2) 3. ����(x4)" << std::endl;
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
			std::cout << "��֧�ֵ����룬��Ϸ�Ѷ�Ĭ��Ϊ��" << std::endl;
			speed = 200;
			break;
		}
		std::cout << "������ʳ��������(-0.02xÿ��λ)" << std::endl;
		std::cin >> foodNum;
		if (foodNum <= 0)
		{
			std::cout << "��֧�ֵ����룬ʳ������Ĭ��Ϊ1" << std::endl;
			foodNum = 1;
		}
		std::cout << "�����붾ҩ������(+0.1xÿ��λ)" << std::endl;
		std::cin >> poisonNum;
		if (poisonNum < 0)
		{
			std::cout << "��֧�ֵ����룬��ҩ����Ĭ��Ϊ0" << std::endl;
			poisonNum = 0;
		}
		std::cout << "�������ϰ���������(+0.2xÿ��λ)" << std::endl;
		std::cin >> wallNum;
		if (wallNum < 0)
		{
			std::cout << "��֧�ֵ����룬�ϰ�������Ĭ��Ϊ0" << std::endl;
			wallNum = 0;
		}
		std::cout << "�Ƿ���������ߣ�1. ��(1x) 2. ��(2x)" << std::endl;
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
			std::cout << "��֧�ֵ����룬�������Ĭ�Ϲر�" << std::endl;
			randomWalk = false;
			break;
		}
		std::cout << "���óɹ������������ʼ��Ϸ" << std::endl;

		Game game(speed, foodNum, poisonNum, wallNum, randomWalk);
		game.gaming();
	}

	return 0;
}