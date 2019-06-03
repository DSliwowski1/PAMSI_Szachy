#include "UI.h"
#include <iostream>
#include <string>
#include "Szachy.h"
#include "Image.h"
#include <sstream>

extern bool ruch;
extern std::string ruchStr;
extern Szachy s;
extern Image imgs[12];
extern int czlowiekPierwszy;

GLuint texIDs[12];


void UI::cursorPositionCallback(GLFWwindow * window, double PosX, double PosY)
{
	std::cout << "x: " << PosX << " y: " << PosY << std::endl;
}

void UI::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	static double oldX, oldY, newX, newY;
	static bool wSrodku;
	wSrodku = false;
	bool validMove = false;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &oldX, &oldY);
		if (oldX < 8 * 64 && oldY < 8 * 64)
		{
			wSrodku = true;
	//		std::cout << "w srodku" << std::endl;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
	//	std::cout << "left realesed" << std::endl;
	//	std::cout << "OxOy" << oldX << oldY << std::endl;

		glfwGetCursorPos(window, &newX, &newY);
		if (newX < 8 * 64 && newY < 8 * 64)
		{
			if ((int)oldY / 64 == 1 && (int)newY / 64 == 0 && s((int)oldY / 64, (int)oldX / 64) == 'P')
			{
				//promocja pionka
	//			std::cout << "Promocja" << std::endl;
	//			std::cout << (int)oldY / 64 << (int)oldX / 64 << (int)newY / 64 << (int)newX / 64 << std::endl;
				std::stringstream ss;
				ss << (int)oldX / 64 << (int)newX / 64 << s((int)newY / 64, (int)newX / 64);
				ruchStr = ss.str();
				ruchStr += "QP";
			}
			else
			{
				//normalny ruch
				std::stringstream ss;
				ss << (int)oldY / 64 << (int)oldX / 64 << (int)newY / 64 << (int)newX / 64 << s((int)newY / 64, (int)newX / 64);
				ruchStr = ss.str();
			}
		//	std::cout << ruchStr << std::endl;
			std::string mozliwe = s.MozliweRuchy();

			if (mozliwe.empty())
			{
				std::cout << "Szach mat! Przegra³eœ!" << std::endl;
				return;
			}

			if (mozliwe.find(ruchStr) != std::string::npos) //Jezeli wykonany ruch jest mozliwy
			{
				s.ZrobRuch(ruchStr);
				UI::RysujPlansze();
				glfwSwapBuffers(window);

				s.ObrocPlansze();
				std::cout << "Mysle nad ruchem" << std::endl;
				std::string tmp = s.AlfaBeta(4, P_INF, N_INF, 0, "");
//				std::cout << tmp << std::endl;
				s.ZrobRuch(tmp);
				s.ObrocPlansze();

//				UI::RysujPlansze();
			}
		}
	}
	
}

void UI::RysujPlansze()
{
	int Szerokosc = 64;
	Graphic g;

	int r;
	int c;

	for (int i = 0; i < 64; i += 2) {
		g.FillRec((i % 8 + (i / 8) % 2)*Szerokosc + Szerokosc / 2, (i / 8)*Szerokosc + Szerokosc / 2, Szerokosc, Szerokosc, 252, 206, 148);
		g.FillRec(((i + 1) % 8 - ((i + 1) / 8) % 2)*Szerokosc + Szerokosc / 2, ((i + 1) / 8)*Szerokosc + Szerokosc / 2, Szerokosc, Szerokosc, 164, 98, 28);
	}
	for (int i = 0; i < 64; i++)
	{
		r = i / 8;
		c = i % 8;
		if (czlowiekPierwszy == 1)
		{
			switch (s(r, c))
			{
			case 'P':
				g.DrawImage(imgs[0], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				//	g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				//	f.Draw(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'R':
				g.DrawImage(imgs[1], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				//	g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);

				break;
			case 'K':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[2], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'B':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[3], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'Q':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[4], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'A':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[5], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;

			case 'p':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[6], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'r':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[7], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'k':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[8], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'b':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[9], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'q':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[10], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'a':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[11], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			}
		}
		else if (czlowiekPierwszy == 0)
		{
			switch (s(r, c))
			{
			case 'p':
				g.DrawImage(imgs[0], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				//	g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				//	f.Draw(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'r':
				g.DrawImage(imgs[1], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				//	g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);

				break;
			case 'k':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[2], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'b':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[3], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'q':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[4], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'a':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[5], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;

			case 'P':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[6], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'R':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[7], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'K':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[8], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'B':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[9], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'Q':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[10], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			case 'A':
				//g.DrawRec(c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2, 32, 32);
				g.DrawImage(imgs[11], c* Szerokosc + Szerokosc / 2, r* Szerokosc + Szerokosc / 2);
				break;
			}
		}
	}
}

void UI::LoadSzachy()
{
	static GLuint texIDs[12];
	imgs[0].Load("PB.png");
	imgs[1].Load("RB.png");
	imgs[2].Load("KB.png");
	imgs[3].Load("BB.png");
	imgs[4].Load("QB.png");
	imgs[5].Load("AB.png");

	imgs[6].Load("PC.png");
	imgs[7].Load("RC.png");
	imgs[8].Load("KC.png");
	imgs[9].Load("BC.png");
	imgs[10].Load("QC.png");
	imgs[11].Load("AC.png");

	//f.LoadTexture(imgs[0]);

}
