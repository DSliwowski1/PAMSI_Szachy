#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <chrono>

#include "Graphic.h"
#include "UI.h"
//#include "UI.cpp"

#include "Szachy.h"

#define WND_WIDTH 512
#define WND_HEIGHT 512




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
	int pojedynek = -1;

	GLFWwindow* window;

	UI::LoadSzachy();


	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WND_WIDTH, WND_HEIGHT, "Szachy", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/*Ustawienie Callback myszki*/
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetMouseButtonCallback(window, UI::mouseButtonCallback);

	//Ustawienie sposobu wyœwietlania kana³u alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Ustawienie rzutowania na 2D
	glMatrixMode(GL_PROJECTION); 
	glOrtho(0, WND_WIDTH, WND_HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW); 


	while (!poprawne)
	{
		czlowiekPierwszy = -1;

		cout << "Kto ma zaczynaæ? 0 - komputer, 1 - ty" << endl;
		cin >> czlowiekPierwszy;
		if (czlowiekPierwszy == 1 || czlowiekPierwszy == 0)
			poprawne = true;
	}


	UI::RysujPlansze();

	if (czlowiekPierwszy == 0)
	{
		std::cout << "Mysle nad ruchem" << std::endl;
		s.ZrobRuch(s.AlfaBeta(4, P_INF, N_INF, 0, ""));
		s.ObrocPlansze();
	}

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		UI::RysujPlansze();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		if (s.CzyKoniec())
			system("PAUSE");

	}

	glfwTerminate();


	return 0;
	
}