#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <random>
#include <iomanip>

constexpr size_t WIDTH = 20;
constexpr size_t HEIGHT = 40;

struct Point
{
	int x, y;

	Point(int x, int y) : x(x), y(y) {}
	void operator=(const Point& p) { x = p.x; y = p.y; }
	bool operator==(const Point& p) const { return x == p.x && y == p.y; }
	bool operator!=(const Point& p) const { return x != p.x || y != p.y; }
	Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
	Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
};

struct Body
{
	Point pos;
	Point dir;

	Body(Point p, Point dir) : pos(p), dir(dir) {}
	void operator=(const Body& b) { pos = b.pos; dir = b.dir; }
	void move() { pos = pos + dir; }
	Body moved() const { return Body(pos + dir, dir); }
	void changeDir(Point d) { dir = d; }
};

class Snake
{
private:
	std::vector<Body> body;
	int length = 1;
	int initSpeed = 200;
	bool isAlive = true;

public:
	Snake() { body.push_back(Body(Point(WIDTH / 2, HEIGHT / 2), Point(1, 0))); }
	Snake(Point p) { body.push_back(Body(p, Point(1, 0))); }
	Snake(Point p, int s) : initSpeed(s) { body.push_back(Body(p, Point(1, 0))); }
	std::vector<Point> getPos() const { std::vector<Point> pos; for (auto& b : body) pos.push_back(b.pos); return pos; }
	Point getHead() const { return body[0].pos; }
	Point getDir() const { return body[0].dir; }
	int getLength() const { return length; }
	int getInitSpeed() const { return initSpeed; }
	int getSpeed() const { return int(initSpeed * pow(0.9, length / 5)); }
	bool isDead() const { return !isAlive || length == 0; }
	void die() { isAlive = false; }
	void changeDir(Point d) { body[0].changeDir(d); }
	void move();
	void grow() { body.push_back(Body(body.back().pos - body.back().dir, body.back().dir)); length++; }
	void shrink() { body.pop_back(); length--; }
};

struct GridPoint
{
	Point pos;
	bool isHead = false;
	bool isBody = false;
	bool isWall = false;
	bool isFood = false;
	bool isPotion = false;

	GridPoint() : pos(Point(0, 0)) {}
	GridPoint(Point p) : pos(p) {}
};

class Grid
{
private:
	GridPoint grid[WIDTH][HEIGHT];
	void embedSnake(Snake& s);

public:
	Grid();
	void generateFood(size_t num = 1);
	void generatePotion(size_t num = 1);
	void update(Snake& s);
	void print() const;
};

class Game
{
private:
	Grid grid;
	Snake snake;
	double multiplier = 1.0;
	double score = 0.0;
	int key = 0;
	int foodNum = 1;
	int potionNum = 0;
	void waitKey();
	void getKey();

public:
	Game() {}
	Game(int s, int food, int potion) : snake(Point(WIDTH / 2, HEIGHT / 2), s), foodNum(food), potionNum(potion) {}
	void init();
	void gaming();
	void update();
	void print() const;
	double getMultiplier() const
	{
		return (1.0 - 0.02 * (foodNum - 1) + 0.2 * potionNum) *
			pow(1.1, snake.getLength() / 5) * (200.0 / snake.getInitSpeed());
	}
};

inline void pointat(size_t x, size_t y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#endif