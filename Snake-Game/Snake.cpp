#include "SnakeGame.h"

bool Snake::intersectSelf()
{
	for (size_t i = 1; i < body.size(); i++)
	{
		if (body[0].pos == body[i].pos)
		{
			isAlive = false;
			return true;
		}
	}
	return false;
}

bool Snake::intersectWall()
{
	if (body[0].pos.x == 0 || body[0].pos.x == WIDTH - 1 || body[0].pos.y == 0 || body[0].pos.y == HEIGHT - 1)
	{
		isAlive = false;
		return true;
	}
	return false;
}

void Snake::move()
{
	body[0].move();
	if (intersectWall() || intersectSelf())
		return;
	for (size_t i = 1; i < body.size(); i++)
	{
		body[i].move();
		if (body[i].moved().pos != body[i - 1].pos)
		{
			body[i].changeDir(body[i - 1].pos - body[i].pos);
		}
	}
}

int Snake::getSpeed() const
{
	int speed = int(200 * pow(0.9, length / 5));
	return speed;
}