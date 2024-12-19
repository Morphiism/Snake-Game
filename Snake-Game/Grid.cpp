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
	for (size_t i = 1; i < pos.size(); i++)
	{
		grid[pos[i].x][pos[i].y].isBody = true;
	}
}

void Grid::generateFood(size_t num)
{
	size_t count = 0;
	while (count < num)
	{
		int x = distX(gen);
		int y = distY(gen);
		if (grid[x][y].isEmpty())
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
		if (grid[x][y].isEmpty())
		{
			grid[x][y].isPoison = true;
			count++;
		}
	}
}

void Grid::generateWall(size_t num)
{
	size_t count = 0;
	while (count < num)
	{
		int x = distX(gen);
		int y = distY(gen);
		if (grid[x][y].isEmpty())
		{
			grid[x][y].isWall = true;
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
			grid[i][j].isBody = false;
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
	else if (grid[head.x][head.y].isPoison)
	{
		s.shrink();
		grid[head.x][head.y].isPoison = false;
		generatePotion();
	}
	else if (grid[head.x][head.y].isWall || grid[head.x][head.y].isBody)
	{
		s.die();
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
			else if (grid[i][j].isBody)
				std::cout << "B";
			else if (grid[i][j].isFood)
				std::cout << "F";
			else if (grid[i][j].isPoison)
				std::cout << "P";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

Point Grid::randomDir()
{
	std::uniform_int_distribution<int> distDir(0, 3);
	int dir = distDir(gen);
	switch (dir)
	{
	case 0:
		return Point(-1, 0);
	case 1:
		return Point(1, 0);
	case 2:
		return Point(0, -1);
	case 3:
		return Point(0, 1);
	}
}

void Grid::randomWalk()
{
	std::vector<Point> foods, poisons;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (grid[i][j].isFood)
				foods.push_back(Point(i, j));
			else if (grid[i][j].isPoison)
				poisons.push_back(Point(i, j));
		}
	}
	for (Point food : foods)
	{
		Point dir = randomDir();
		Point next = food + dir;
		if (grid[next.x][next.y].isEmpty())
		{
			grid[food.x][food.y].isFood = false;
			grid[next.x][next.y].isFood = true;
		}
	}
	for (Point poison : poisons)
	{
		Point dir = randomDir();
		Point next = poison + dir;
		if (grid[next.x][next.y].isEmpty())
		{
			grid[poison.x][poison.y].isPoison = false;
			grid[next.x][next.y].isPoison = true;
		}
	}
}