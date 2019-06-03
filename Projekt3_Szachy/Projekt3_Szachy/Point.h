#pragma once

class Point {
private:
	int _x;
	int _y;
public:
	int GetX() { return _x; }
	int GetY() { return _y; }
	void SetX(int a) { _x = a; }
	void SetY(int a) { _y = a; }
public:
	Point(int x, int y) : _x(x), _y(y) {}
};