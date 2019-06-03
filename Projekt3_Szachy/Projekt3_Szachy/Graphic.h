#pragma once

#include "GLFW/glfw3.h"
#include "Point.h"
#include "Image.h"

class Graphic	{
public:
	void DrawLine(int x1, int y1, int x2, int y2);
//	void DrawCircle(int x, int y, int r);
	void DrawRec(int x, int y, int width, int height);
	void FillRec(int x, int y, int width, int height, int r, int g, int b );
	void DrawPolygon(Point *arr, int size);
	void DrawImage(Image &img, int x, int y);
};