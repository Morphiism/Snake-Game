#include "SnakeGame.h"

int main()
{
	int speedMode;
	int speed;
	int foodNum;
	int poisonNum;
	int wallNum;
	while (true)
	{
		system("cls");
		SetConsoleTitle(TEXT("̰����"));
		std::cout << "��ѡ����Ϸ�Ѷȣ�1. �� 2. �е� 3. ����" << std::endl;
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
		std::cout << "������ʳ��������" << std::endl;
		std::cin >> foodNum;
		if (foodNum <= 0)
		{
			std::cout << "��֧�ֵ����룬ʳ������Ĭ��Ϊ1" << std::endl;
			foodNum = 1;
		}
		std::cout << "�����붾ҩ������" << std::endl;
		std::cin >> poisonNum;
		if (poisonNum < 0)
		{
			std::cout << "��֧�ֵ����룬��ҩ����Ĭ��Ϊ0" << std::endl;
			poisonNum = 0;
		}
		std::cout << "�������ϰ���������" << std::endl;
		std::cin >> wallNum;
		if (wallNum < 0)
		{
			std::cout << "��֧�ֵ����룬�ϰ�������Ĭ��Ϊ0" << std::endl;
			wallNum = 0;
		}
		std::cout << "���óɹ������������ʼ��Ϸ" << std::endl;

		Game game(speed, foodNum, poisonNum, wallNum);
		game.gaming();
	}

	return 0;
}