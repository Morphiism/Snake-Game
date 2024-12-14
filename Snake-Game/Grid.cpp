#include "SnakeGame.h"

Grid::Grid()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			grid[i][j] = GridPoint(Point(i, j));
		}
	}
}

void Grid::embedSnake(Snake& s)
{
	std::vector<Point> pos = s.getPos();
	grid[pos[0].x][pos[0].y].isHead = true;
	for (size_t i = 0; i < pos.size(); i++)
	{
		grid[pos[i].x][pos[i].y].isSnake = true;
	}
}

void Grid::generateFood()
{
	while (true)
	{
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;
		if (!grid[x][y].isSnake)
		{
			grid[x][y].isFood = true;
			break;
		}
	}
}

void Grid::update(Snake& s)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			grid[i][j].isHead = false;
			grid[i][j].isSnake = false;
		}
	}
	embedSnake(s);
	Point head = s.getHead();
	if (grid[head.x][head.y].isFood)
	{
		s.grow();
		deleteFood(head);
		generateFood();
	}
}

void Grid::print() const
{
	system("cls");
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1)
				std::cout << "#";
			else if (grid[i][j].isHead)
				std::cout << "H";
			else if (grid[i][j].isSnake)
				std::cout << "S";
			else if (grid[i][j].isFood)
				std::cout << "F";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}
}