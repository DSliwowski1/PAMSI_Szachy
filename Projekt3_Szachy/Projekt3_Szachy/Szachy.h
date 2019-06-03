#pragma once

#include <string>

#include "Graphic.h"
#include "Image.h"
//#include "UI.h"

class Szachy : private Graphic{
private:
	char plansza[8][8]={
		{'r','k','b','q','a','b','k','r'},
		{'p','p','p','p','p','p','p','p'},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{'P','P','P','P','P','P','P','P'},
		{'R','K','B','Q','A','B','K','R'}
	};
	/*char plansza[8][8] = {
		{' ',' ',' ',' ','a',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ','A',' ',' ',' '}
	};*/
	/*
	Objasnienie Plnaszy
	Kolor pionków:
		mala litera - czarne
		Duza litera - bia³e
	Figury:
	p/P	- Pionek
	r/R	- Wieza
	k/K	- Skoczek
	b/B	- Goniec
	q/Q - Hetman
	a/A	- Król
 	' ' - puste pole
	*/

	int PozKrolD = 0, PozKrolM = 0;		//Pozwalaj¹ na u³atwiona sprawdzenie czy król jest szachownay
	int MakGlebokosc = 4;			//Maksymalna glebokoœæ do której dochodzi rekurencja
	int Szerokosc=64;


private:

	std::string  mozliweP(int i);
	std::string  mozliweR(int i);
	std::string  mozliweK(int i);
	std::string  mozliweB(int i);
	std::string  mozliweQ(int i);
	std::string  mozliweA(int i);

	bool KrolBezpieczny();


private:
	class Ewaluacja
	{
	public:
		int ewaluacja(Szachy  &s, std::string lista, int glebokosc);
	private:
		int ewaluacjaAtaku(Szachy  &s);
		int ewaluacjaFigury(Szachy  &s );
		int ewaluacjaMobinosci(Szachy  &s, int iloscRuchow, int glebokosc);
		int ewaluacjaPozycji(Szachy  &s, int figura);

	private:
		//Tablice ruchów
		int pionekTab[8][8] = {
			{0,  0,  0,  0,  0,  0,  0,  0},
			{50, 50, 50, 50, 50, 50, 50, 50},
			{10, 10, 20, 30, 30, 20, 10, 10},
			{ 5,  5, 10, 25, 25, 10,  5,  5 },
			{ 0,  0,  0, 20, 20,  0,  0,  0 },
			{ 5, -5,-10,  0,  0,-10, -5,  5 },
			{ 5, 10, 10,-20,-20, 10, 10,  5 },
			{ 0,  0,  0,  0,  0,  0,  0,  0 } };

		int skoczekTab[8][8] = {
			{-50,-40,-30,-30,-30,-30,-40,-50},
			{-40,-20,  0,  0,  0,  0,-20,-40},
			{-30,  0, 10, 15, 15, 10,  0,-30},
			{-30,  5, 15, 20, 20, 15,  5,-30},
			{-30,  0, 15, 20, 20, 15,  0,-30},
			{-30,  5, 10, 15, 15, 10,  5,-30},
			{-40,-20,  0,  5,  5,  0,-20,-40},
			{-50,-40,-30,-30,-30,-30,-40,-50} };

		int goniecTab[8][8] = {
			{-20,-10,-10,-10,-10,-10,-10,-20},
			{-10,  0,  0,  0,  0,  0,  0,-10},
			{-10,  0,  5, 10, 10,  5,  0,-10},
			{-10,  5,  5, 10, 10,  5,  5,-10},
			{-10,  0, 10, 10, 10, 10,  0,-10},
			{-10, 10, 10, 10, 10, 10, 10,-10},
			{-10,  5,  0,  0,  0,  0,  5,-10},
			{-20,-10,-10,-10,-10,-10,-10,-20}};

		int wierzaTab[8][8] = {
			{20,-10,-10,-10,-10,-10,-10,-20},
			{-10,  0,  0,  0,  0,  0,  0,-10},
			{-10,  0,  5, 10, 10,  5,  0,-10},
			{-10,  5,  5, 10, 10,  5,  5,-10},
			{-10,  0, 10, 10, 10, 10,  0,-10},
			{-10, 10, 10, 10, 10, 10, 10,-10},
			{-10,  5,  0,  0,  0,  0,  5,-10},
			{-20,-10,-10,-10,-10,-10,-10,-20} };

		int hetmanTab[8][8] = {
			{-20,-10,-10, -5, -5,-10,-10,-20},
			{-10,  0,  0,  0,  0,  0,  0,-10},
			{-10,  0,  5,  5,  5,  5,  0,-10},
			{-5,  0,  5,  5,  5,  5,  0, -5},
			{0,  0,  5,  5,  5,  5,  0, -5},
			{-10,  5,  5,  5,  5,  5,  0,-10},
			{-10,  0,  5,  0,  0,  0,  0,-10},
			{-20,-10,-10, -5, -5,-10,-10,-20} };;

		int krolMidTab[8][8] = {
			{-30,-40,-40,-50,-50,-40,-40,-30},
			{-30,-40,-40,-50,-50,-40,-40,-30},
			{-30,-40,-40,-50,-50,-40,-40,-30},
			{-30,-40,-40,-50,-50,-40,-40,-30},
			{-20,-30,-30,-40,-40,-30,-30,-20},
			{-10,-20,-20,-20,-20,-20,-20,-10},
			{20, 20,  0,  0,  0,  0, 20, 20},
			{20, 30, 10,  0,  0, 10, 30, 20} };

		int krolEndTab[8][8] = {
			{-50,-40,-30,-20,-20,-30,-40,-50},
			{-30,-20,-10,  0,  0,-10,-20,-30},
			{-30,-10, 20, 30, 30, 20,-10,-30},
			{-30,-10, 30, 40, 40, 30,-10,-30},
			{-30,-10, 30, 40, 40, 30,-10,-30},
			{-30,-10, 20, 30, 30, 20,-10,-30},
			{-30,-30,  0,  0,  0,  0,-30,-30},
			{-50,-30,-30,-30,-30,-30,-30,-50} };

	};

	Ewaluacja e;

public:
	Szachy();
	void Print();
	char operator()(int x, int y) 
	{
		return this->plansza[x][y];
	}
	int GetPosKrolD() { return this->PozKrolD; }
	void SetPosKrolD(int a) { this->PozKrolD = a; }

	//Pamietaj o przeniesienu do privat na koniec
	std::string MozliweRuchy();
	void ZrobRuch(std::string ruch);
	void CofnijRuch(std::string ruch);
	std::string AlfaBeta(int glebokosc, int beta, int alfa, int gracz, std::string ruch);
	std::string SortujRuchy(std::string lista);

	void ObrocPlansze();




};