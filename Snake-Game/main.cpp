#include "SnakeGame.h"

int main()
{
	int speedMode;
	int speed;
	int foodNum;
	while (true)
	{
		system("cls");
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
		std::cout << "���óɹ������������ʼ��Ϸ" << std::endl;

		Game game(speed, foodNum);
		game.gaming();
	}

	return 0;
}