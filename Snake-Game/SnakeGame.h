#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <random>

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
	void changeDir(Point& d) { dir = d; }
};

class Snake
{
private:
	std::vector<Body> body;
	int length;
	bool isAlive;
	bool intersectSelf();
	bool intersectWall();

public:
	Snake() : length(1), isAlive(true) { body.push_back(Body(Point(WIDTH / 2, HEIGHT / 2), Point(1, 0))); }
	Snake(Point p) : length(1), isAlive(true) { body.push_back(Body(p, Point(1, 0))); }
	std::vector<Point> getPos() const { std::vector<Point> pos; for (auto& b : body) pos.push_back(b.pos); return pos; }
	Point getHead() const { return body[0].pos; }
	int getLength() const { return length; }
	bool isDead() const { return !isAlive; }
	void changeDir(Point d) { body[0].changeDir(d); }
	void move();
	void grow() { body.push_back(Body(body.back().pos - body.back().dir, body.back().dir)); length++; }
};

struct GridPoint
{
	Point pos;
	bool isHead;
	bool isSnake;
	bool isFood;

	GridPoint() : pos(Point(0, 0)), isHead(false), isSnake(false), isFood(false) {}
	GridPoint(Point p) : pos(p), isHead(false), isSnake(false), isFood(false) {}
};

class Grid
{
private:
	GridPoint grid[WIDTH][HEIGHT];
	void embedSnake(Snake& s);
	void deleteFood(Point& p) { grid[p.x][p.y].isFood = false; }

public:
	Grid();
	void generateFood();
	void update(Snake& s);
	void print() const;
};

class Game
{
private:
	Grid grid;
	Snake snake;
	int key;
	void waitKey();
	void getKey();

public:
	Game();
	void init();
	void gaming();
	void update();
	void print() const;
};