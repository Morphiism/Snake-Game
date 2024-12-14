#include "SnakeGame.h"

int main()
{
	Grid grid;
	Snake snake(Point(WIDTH / 2, HEIGHT / 2));
	grid.update(snake);
	grid.print();

	snake.move();
	grid.update(snake);
	grid.print();

	return 0;
}