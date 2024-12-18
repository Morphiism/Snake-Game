#include "SnakeGame.h"

void Snake::move()
{
	body[0].move();
	for (size_t i = 1; i < body.size(); i++)
	{
		body[i].move();
		if (body[i].moved().pos != body[i - 1].pos)
		{
			body[i].changeDir(body[i - 1].pos - body[i].pos);
		}
	}
}