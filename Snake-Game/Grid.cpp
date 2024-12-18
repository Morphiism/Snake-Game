#include "SnakeGame.h"

std::random_device rng;
std::mt19937 gen(rng());
std::uniform_int_distribution<int> distX(1, WIDTH - 2);
std::uniform_int_distribution<int> distY(1, HEIGHT - 2);

Grid::Grid()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			grid[i][j] = GridPoint(Point(i, j));
			if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1)
				grid[i][j].isWall = true;
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

void Grid::generateFood(size_t num)
{
	size_t count = 0;
	while (count < num)
	{
		int x = distX(gen);
		int y = distY(gen);
		if (!grid[x][y].isSnake && !grid[x][y].isFood && !grid[x][y].isPotion)
		{
			grid[x][y].isFood = true;
			count++;
		}
	}
}

void Grid::generatePotion(size_t num)
{
	size_t count = 0;
	while (count < num)
	{
		int x = distX(gen);
		int y = distY(gen);
		if (!grid[x][y].isSnake && !grid[x][y].isFood && !grid[x][y].isPotion)
		{
			grid[x][y].isPotion = true;
			count++;
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
		grid[head.x][head.y].isFood = false;
		generateFood();
	}
	else if (grid[head.x][head.y].isPotion)
	{
		s.shrink();
		grid[head.x][head.y].isPotion = false;
		generatePotion();
	}
}

void Grid::print() const
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			if (grid[i][j].isWall)
				std::cout << "#";
			else if (grid[i][j].isHead)
				std::cout << "H";
			else if (grid[i][j].isSnake)
				std::cout << "B";
			else if (grid[i][j].isFood)
				std::cout << "F";
			else if (grid[i][j].isPotion)
				std::cout << "P";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}