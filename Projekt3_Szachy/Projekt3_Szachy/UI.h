#pragma once
#include "GLFW/glfw3.h"
#include "Szachy.h"
#include "Image.h"

#define P_INF 100000000
#define N_INF -100000000

//bool ruch;


class UI {
public:
	static void cursorPositionCallback(GLFWwindow *window, double PosX, double PosY);
	static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

	static void RysujPlansze();
	static void LoadSzachy();
private:

};