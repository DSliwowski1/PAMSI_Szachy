#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <chrono>

#include "Graphic.h"
#include "UI.h"
//#include "UI.cpp"

#include "Szachy.h"

#define WND_WIDTH 600
#define WND_HEIGHT 600




using std::cout;
using std::cin;
using std::endl;

bool ruch;
std::string ruchStr = "";
Szachy s;
Image imgs[12];
int czlowiekPierwszy = -1;

int main(void)
{
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<double> duration;


	bool poprawne = false;

	GLFWwindow* window;


	UI::LoadSzachy();

	while (!poprawne)
	{
		czlowiekPierwszy = -1;

		cout << "Kto ma zaczynaæ? 0 - komputer, 1 - ty" << endl;
		cin >> czlowiekPierwszy;
		if (czlowiekPierwszy == 1 || czlowiekPierwszy == 0)
			poprawne = true;
	}


	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WND_WIDTH, WND_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	//glfwSetCursorPosCallback(window, UI::cursorPositionCallback);
	glfwSetMouseButtonCallback(window, UI::mouseButtonCallback);

	//Ustawienie sposobu wyœwietlania kana³u alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Ustawienie rzutowania na 2D
	glMatrixMode(GL_PROJECTION); 
	glOrtho(0, WND_WIDTH, WND_HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW); 

//	UI::tmpMain = false;

	//glScalef(1.5f, 1.5f, 1.f);
	/* Loop until the user closes the window */

	UI::RysujPlansze();

	if (czlowiekPierwszy == 0)
	{
		std::cout << "Mysle nad ruchem" << std::endl;
		start = std::chrono::high_resolution_clock::now();
		s.ZrobRuch(s.AlfaBeta(4, P_INF, N_INF, 0, ""));
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		cout << "Czas: " << duration.count() << endl;
		s.ObrocPlansze();
	}

	bool tmpc = true;
	bool tmpb = true;


	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		UI::RysujPlansze();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		

	}

	glfwTerminate();


	return 0;
	
}