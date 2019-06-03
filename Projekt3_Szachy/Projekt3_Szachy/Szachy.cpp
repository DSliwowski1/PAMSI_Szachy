#include "Szachy.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <cctype>


#pragma warning(disable : 4996)


using std::string;

void Szachy::Print()
{
	for (int i = 0; i < 64; ++i)
	{
		int r = i / 8; 
		int c = i % 8;

		std::cout << "'" << plansza[r][c] << "', ";
		if (c == 7)
			std::cout << std::endl;
	}
}

void Szachy::ZrobRuch(std::string ruch)
{
	if (!isdigit(ruch.at(0)))
	{
		std::cout << "Szach mat! Wygra�e�" << std::endl;
		return;
	}

	if (ruch.at(4) != 'P')
	{	//Format danych: x1y1x2y2figura
		//Konwersie na int
		int x1 = ruch.at(0) - '0';
		int y1 = ruch.at(1) - '0';
		int x2 = ruch.at(2) - '0';
		int y2 = ruch.at(3) - '0';

		plansza[x2][y2] = plansza[x1][y1];				//W pole celu wpisujemy co to bylo na poczatku
		plansza[x1][y1] = ' ';							//W pole pocz�tku wpisujemy puste

		if (plansza[x2][y2] == 'A')						//Je�eli ruszamy kr�lem, to muszimy zaktualizowac jego pozycje
		{
			PozKrolD = x2 * 8 + y2;
		}
	}
	else
	{	//y1y2zbitanowaP	(P-promocja)
		//Nast�pi�a promocja pionka
		//Konwersie na int
		int y1 = ruch.at(0) - '0';
		int y2 = ruch.at(1) - '0';

		plansza[1][y1] =' ';		//W pole pocz�tkowe wpisujemy puste
		plansza[0][y2] = ruch[3];	//W pole ko�cowe tow co sie zmienilismy
	}
}

void Szachy::CofnijRuch(std::string ruch)
{
	if (ruch.at(4) != 'P')
	{	//Format danych: x1y1x2y2figura
		//Konwersie na int
		int x1 = ruch.at(0) - '0';
		int y1 = ruch.at(1) - '0';
		int x2 = ruch.at(2) - '0';
		int y2 = ruch.at(3) - '0';

		plansza[x1][y1] = plansza[x2][y2];			//W pole pocz�tku wpisujemy to co mielismy
		plansza[x2][y2] = ruch.at(4);				//W pole celu wpisujemy co to bylo na poczatku

		if (plansza[x1][y1] == 'A')					//Je�eli ruszamy kr�lem, to muszimy zaktualizowac jego pozycje
		{
			PozKrolD = x1 * 8 + y1;
		}
	}
	else
	{	//y1y2zbitanowaP	(P-promocja)
		//Nast�pi�a promocja pionka
		//Konwersie na int
		int y1 = ruch.at(0) - '0';
		int y2 = ruch.at(1) - '0';

		plansza[1][y1] = 'P';		//W pole pocz�tkowe wpisujemy puste
		plansza[0][y2] = ruch.at(2);				//W pole ko�cowe tow co sie zmienilismy
	}
}



//Zwraca wszystie mo�liwe ruychy na planszy
//Format danych: x1y1x2y2figura
//x1,y2 - poczatkowa pozycja
//x2,y2 - koncowa pozycja
//pionek - symbol zbitej figury(spacja jezeli jej nie bylo)
string Szachy::MozliweRuchy()	
{
	string list = "";	//Wynik
	int r, c;
	for (int i = 0; i < 64; i++)	//Przejdz po wszystkich polach
	{
		r = i / 8;
		c = i % 8;
		switch (plansza[r][c])	//Jezeli jest biala figura, to dodaj jego ruchy do listy
		{
		case 'P':	
			list += mozliweP(i);
			break;
		case 'R':
			list += mozliweR(i);
			break;
		case 'K':
			list += mozliweK(i);
			break;
		case 'B':
			list += mozliweB(i);
			break;
		case 'Q':
			list += mozliweQ(i);
			break;
		case 'A':
			list += mozliweA(i);
			break;
		default:
			break;
		}
	}
	return list;
}

//regu�y ruchu pionka
std::string Szachy::mozliweP(int i)
{
	string lista = "";								//(1, -1)  (1, 0)   (1, 1)
	string tmp;										//(0, -1)    R      (0, 1)
	char old;										//(-1,-1)  (-1, 0)  (-1,1)
	int r = i / 8;									
	int c = i % 8;									
	
	for (int j = -1; j <= 1; j += 2) {	
		//Zbicie
		if (iswlower(plansza[r - 1][c + j]) && i >= 16 &&						//Jezeli po ukosie jest figura przeciwnika
			r - 1 >= 0 && r - 1 < 8 && c + j >= 0 && c + j < 8)		//i jeste�my w polu
		{
			old = plansza[r - 1][c + j];								//zachowaj stara figure
			plansza[r][c] = ' ';									//"Podnies" pionek
			plansza[r - 1][c + j] = 'P';							//"Po��" w nowym miejscu
			if (KrolBezpieczny())									//Jezeli ten ruch nie gorzi szachem
			{
				std::stringstream ss;								//tworzymy strumien
				ss << r << c << (r - 1) << (c + j);				//wpisujemy w niego liczby
				tmp = ss.str();										//Tworzymy z niego string
				lista += tmp;										//Dodajemy do wyniku
				lista += old;
			}
			//Je�eli kr�l by� szachowany po ruchu cofnij ruch
			plansza[r][c] = 'P';									//PRzesun pionek
			plansza[r - 1][c + j] = old;								//Przywr�� figure	
		}
		
		//Zbicie i promocja
		if (iswlower(plansza[r - 1][c + j]) && i < 16 &&			//Jezeli po ukosie jest figura przeciwnika
			r - 1 >= 0 && r - 1 < 8 && c + j >= 0 && c + j < 8)		//i jeste�my w polu
		{
			char prom[] = { 'Q', 'B', 'K', 'R' };					//Wszystkie mozliwosci promocji
			for (int k = 0; k < 4; k++)
			{
				old = plansza[r - 1][c + j];						//zachowaj stara figure
				plansza[r][c] = ' ';								//"Podnies" pionek
				plansza[r - 1][c + j] = prom[k];					//"Po��" w nowym miejscu
				if (KrolBezpieczny())								//Jezeli ten ruch nie gorzi szachem
				{
					//W przypadku pormocji dane wygladaja:  y1, y2, zbita, nowa, P (P-promocja)
					std::stringstream ss;							//tworzymy strumien
					ss << c << (c + j);								//wpisujemy w niego liczby
					tmp = ss.str();									//Tworzymy z niego string
					lista += tmp;									//Dodajemy do wyniku
					lista += old;
					lista += prom[k];
					lista += 'P';
				}
				//Je�eli kr�l by� szachowany po ruchu cofnij ruch
				plansza[r][c] = 'P';								//PRzesun pionek
				plansza[r - 1][c + j] = old;						//Przywr�� figure	
			}
		}
	}

	//Ruch jeden w gore
	if (plansza[r - 1][c] == ' ' && i >= 16 &&					//Jezeli przed nami jest wolne pole
		r - 1 >= 0 && r - 1 < 8 && c >= 0 && c < 8)				//i jeste�my na planszy
	{
		old = plansza[r - 1][c];								//zachowaj stara figure
		plansza[r][c] = ' ';									//"Podnies" pionek
		plansza[r - 1][c] = 'P';								//"Po��" w nowym miejscu
		if (KrolBezpieczny())									//Jezeli ten ruch nie gorzi szachem
		{
			std::stringstream ss;								//tworzymy strumien
			ss << r << c << (r - 1) << (c);						//wpisujemy w niego liczby
			tmp = ss.str();										//Tworzymy z niego string
			lista += tmp;										//Dodajemy do wyniku
			lista += old;
		}
		//Je�eli kr�l by� szachowany po ruchu cofnij ruch
		plansza[r][c] = 'P';									//PRzesun pionek
		plansza[r - 1][c] = old;								//Przywr�� figure	
	}

	//Ruch dwa w gore
	if (plansza[r - 1][c] == ' ' && r == 6 &&					//Jezeli przed nami dwa pola s� wolne
		plansza[r - 2][c] == ' ' &&
		r - 1 >= 0 && r - 1 < 8 && c >= 0 && c < 8)				//i jeste�my w rzedzie 6 i na planszy
	{
		old = plansza[r - 2][c];								//zachowaj stara figure
		plansza[r][c] = ' ';									//"Podnies" pionek
		plansza[r - 2][c] = 'P';								//"Po��" w nowym miejscu
		if (KrolBezpieczny())									//Jezeli ten ruch nie gorzi szachem
		{
			std::stringstream ss;								//tworzymy strumien
			ss << r << c << (r - 2) << (c);						//wpisujemy w niego liczby
			tmp = ss.str();										//Tworzymy z niego string
			lista += tmp;										//Dodajemy do wyniku
			lista += old;
		}
		//Je�eli kr�l by� szachowany po ruchu cofnij ruch
		plansza[r][c] = 'P';									//PRzesun pionek
		plansza[r - 2][c] = old;								//Przywr�� figure	
	}

	//Promocja
	if (plansza[r - 1][c] == ' ' && i < 16 &&					//Jezeli przed nami jest wolne pole
		r - 1 >= 0 && r - 1 < 8 && c >= 0 && c < 8)				//i jeste�my na planszy
	{
		char prom[] = { 'Q', 'B', 'K', 'R' };					//Wszystkie mozliwosci promocji
		for (int k = 0; k < 4; k++)
		{
			old = plansza[r - 1][c];						//zachowaj stara figure
			plansza[r][c] = ' ';								//"Podnies" pionek
			plansza[r - 1][c] = prom[k];					//"Po��" w nowym miejscu
			if (KrolBezpieczny())								//Jezeli ten ruch nie gorzi szachem
			{
				//W przypadku pormocji dane wygladaja:  y1, y2, zbita, nowa, P (P-promocja)
				std::stringstream ss;							//tworzymy strumien
				ss << c << (c);								//wpisujemy w niego liczby
				tmp = ss.str();									//Tworzymy z niego string
				lista += tmp;									//Dodajemy do wyniku
				lista += old;
				lista += prom[k];
				lista += 'P';
			}
			//Je�eli kr�l by� szachowany po ruchu cofnij ruch
			plansza[r][c] = 'P';								//PRzesun pionek
			plansza[r - 1][c] = old;						//Przywr�� figure	
		}
	}
	return lista;
}

//regu�y ruchu wiezy
std::string Szachy::mozliweR(int i)
{
	string lista = "";								//(1, -1)  (1, 0)   (1, 1)
	string tmp;										//(0, -1)    R      (0, 1)
	char old;										//(-1,-1)  (-1, 0)  (-1,1)
	int r = i / 8;									
	int c = i % 8;									
	int count = 1;

	for (int j = -1; j <= 1; j += 2) {
		//Poziomy ruch
		while (plansza[r][c + count * j] == ' ' &&					//Tak d�ugo jak puste pole
			(c + count * j) >= 0 && (c + count * j) < 8)			//i w planszy
		{
			old = plansza[r][c + count * j];						//zachowaj stara figure
			plansza[r][c] = ' ';									//"Podnies" wie�e
			plansza[r][c + count * j] = 'R';						//"Po��" w nowym miejscu
			if (KrolBezpieczny())									//Jezeli ten ruch nie gorzi szachem
			{
				std::stringstream ss;								//tworzymy strumien
				ss << r << c << r << (c + count * j);				//wpisujemy w niego liczby
				tmp = ss.str();										//Tworzymy z niego string
				lista += tmp;										//Dodajemy do wyniku
				lista += old;
			}
			//Je�eli kr�l by� szachowany po ruchu cofnij ruch
			plansza[r][c] = 'R';									//PRzesun wie�e
			plansza[r][c + count * j] = old;						//Przywr�� figure
			count++;
		}
		if (iswlower(plansza[r][c + count * j]) &&					//Je�eli figura przeciwnika
			(c + count * j) >= 0 && (c + count * j) < 8)			//i w planszy
		{
			old = plansza[r][c + count * j];						//zachowaj stara figure
			plansza[r][c] = ' ';									//"Podnies" wie�e
			plansza[r][c + count * j] = 'R';						//"Po��" w nowym miejscu
			if (KrolBezpieczny())									//Jezeli ten ruch nie grozi szachem
			{
				std::stringstream ss;								//tworzymy strumien
				ss << r << c << r << (c + count * j);				//wpisujemy w niego liczby
				tmp = ss.str();										//Tworzymy z niego string
				lista += tmp;										//Dodajemy do wyniku
				lista += old;
			}
			//Je�eli kr�l by� szachowany po ruchu cofnij ruch
			plansza[r][c] = 'R';									//PRzesun wie�e
			plansza[r][c + count * j] = old;						//Przywr�� figure
		}
		count = 1;

		//Pionowy ruch
		while (plansza[r + count * j][c] == ' ' &&					//Tak d�ugo jak puste pole
			(r + count * j) >= 0 && (r + count * j) < 8)			//i w planszy
		{
			old = plansza[r + count * j][c];						//zachowaj stara figure
			plansza[r][c] = ' ';									//"Podnies" wie�e
			plansza[r + count * j][c] = 'R';						//"Po��" w nowym miejscu
			if (KrolBezpieczny())									//Jezeli ten ruch nie gorzi szachem
			{
				std::stringstream ss;								//tworzymy strumien
				ss << r << c << (r + count * j) << c;				//wpisujemy w niego liczby
				tmp = ss.str();										//Tworzymy z niego string
				lista += tmp;										//Dodajemy do wyniku
				lista += old;
			}
			//Je�eli kr�l by� szachowany po ruchu cofnij ruch
			plansza[r][c] = 'R';									//PRzesun wie�e
			plansza[r + count * j][c] = old;						//Przywr�� figure
			count++;
		}
		if (iswlower(plansza[r + count * j][c]) &&					//Je�eli figura przeciwnika
			(r + count * j) >= 0 && (r + count * j) < 8)			//i w planszy
		{
			old = plansza[r + count * j][c];						//zachowaj stara figure
			plansza[r][c] = ' ';									//"Podnies" wie�e
			plansza[r + count * j][c] = 'R';						//"Po��" w nowym miejscu
			if (KrolBezpieczny())									//Jezeli ten ruch nie grozi szachem
			{
				std::stringstream ss;								//tworzymy strumien
				ss << r << c << (r + count * j) << c;				//wpisujemy w niego liczby
				tmp = ss.str();										//Tworzymy z niego string
				lista += tmp;										//Dodajemy do wyniku
				lista += old;
			}
			//Je�eli kr�l by� szachowany po ruchu cofnij ruch
			plansza[r][c] = 'R';									//PRzesun wie�e
			plansza[r + count * j][c] = old;						//Przywr�� figure
		}
		count = 1;	//Ustaw odleg�o�� na 1, aby m�c sprawdzic pozosta�e
	}
	return lista;
}

//regu�y ruchu skoczka
std::string Szachy::mozliweK(int i)
{
	string lista = "";								
	string tmp;										
	char old;										
	int r = i / 8;								
	int c = i % 8;

	for (int j = -1; j <= 1; j+=2) {
		for (int k = -1; k <= 1; k+=2) {
			//Pierwsza po�owa ruch�w
			if (r + j >= 0 && r + j < 8 &&				//Jezeli jest w planszy jest w planszy
				c + 2 * k >= 0 && c + 2 * k < 8) 
			{
				if (iswlower(plansza[r + j][c + 2 * k]) ||				//Jezeli te pole zajmuje przeciwnik
					plansza[r + j][c + 2 * k] == ' ')					//lub jest puste

				{
					old = plansza[r + j][c + 2 * k];						//zachowaj stara figure
					plansza[r][c] = ' ';									//"Podnies" skoczka
					plansza[r + j][c + 2 * k] = 'K';						//"Po��" w nowym miejscu
					if (KrolBezpieczny())									//Jezeli ten ruch nie gorzi szachem
					{
						std::stringstream ss;								//tworzymy strumien
						ss << r << c << (r + j) << (c + 2 * k);				//wpisujemy w niego liczby
						tmp = ss.str();										//Tworzymy z niego string
						lista += tmp;										//Dodajemy do wyniku
						lista += old;
					}
					//Je�eli kr�l by� szachowany po ruchu cofnij ruch
					plansza[r][c] = 'K';									//PRzesun skoczka
					plansza[r + j][c + 2 * k] = old;						//Przywr�� figure
				}
			}
			//Druga po�owa ruch�w
			if (r + j * 2 >= 0 && r + j * 2 < 8 &&								//Jezeli jest w planszy jest w planszy
				c + k >= 0 && c + k < 8)
			{
				if (iswlower(plansza[r+ 2 * j][c + k]) ||				//Jezeli te pole zajmuje przeciwnik
					plansza[r+ 2 * j][c + k] == ' ')					//lub jest puste

				{
					old = plansza[r+ 2 * j][c + k];						//zachowaj stara figure
					plansza[r][c] = ' ';								//"Podnies" skoczka
					plansza[r+ 2 * j][c + k] = 'K';						//"Po��" w nowym miejscu
					if (KrolBezpieczny())								//Jezeli ten ruch nie gorzi szachem
					{
						std::stringstream ss;							//tworzymy strumien
						ss << r << c << (r + 2 * j) << (c + k);			//wpisujemy w niego liczby
						tmp = ss.str();									//Tworzymy z niego string
						lista += tmp;									//Dodajemy do wyniku
						lista += old;
					}
					//Je�eli kr�l by� szachowany po ruchu cofnij ruch
					plansza[r][c] = 'K';								//PRzesun skoczka
					plansza[r+ 2 * j][c + k] = old;						//Przywr�� figure
				}
			}
		}
	}

	return lista;
}

//regu�y ruchu gonca
std::string Szachy::mozliweB(int i)
{
	string lista = "";								//(1, -1)  (1, 0)   (1, 1)
	string tmp;										//(0, -1)    B      (0, 1)
	char old;										//(-1,-1)  (-1, 0)  (-1,1)
	int r = i / 8;									
	int c = i % 8;									
	int count = 1;

	for (int j = -1; j <= 1; j+=2) {										//+=2 pozwala na sprawdzanie jedynie	
		for (int k = -1; k <= 1; k+=2)										//skos�w
		{																	
				while (plansza[r + count * j][c + count * k] == ' ' &&		//Tak d�ugo jak puste pole
					(r + count * j) >= 0 && (r + count * j) < 8 &&			//i w planszy
					(c + count * k) >= 0 && (c + count * k) < 8)
				{
					old = plansza[r + count * j][c + count * k];			//zachowaj stara figure
					plansza[r][c] = ' ';									//"Podnies" go�ca
					plansza[r + count * j][c + count * k] = 'B';			//"Po��" w nowym miejscu
					if (KrolBezpieczny())									//Jezeli ten ruch nie gorzi szachem
					{
						std::stringstream ss;								//tworzymy strumien
						ss << r << c << (r + count * j) << (c + count * k);	//wpisujemy w niego liczby
						tmp = ss.str();										//Tworzymy z niego string
						lista += tmp;										//Dodajemy do wyniku
						lista += old;
					}
					//Je�eli kr�l by� szachowany po ruchu cofnij ruch
					plansza[r][c] = 'B';									//PRzesun go�ca
					plansza[r + count * j][c + count * k] = old;			//Przywr�� figure
					count++;												//Przejd� na nast�pne pole
				}
				if (iswlower(plansza[r + count * j][c + count * k]) &&		//Je�eli figura przeciwnika
					(r + count * j) >= 0 && (r + count * j) < 8 &&			//i w planszy
					(c + count * k) >= 0 && (c + count * k) < 8)
				{
					old = plansza[r + count * j][c + count * k];			//zachowaj stara figure
					plansza[r][c] = ' ';									//"Podnies" go�ca
					plansza[r + count * j][c + count * k] = 'B';			//"Po��" w nowym miejscu
					if (KrolBezpieczny())									//Jezeli ten ruch nie grozi szachem
					{
						std::stringstream ss;								//tworzymy strumien
						ss << r << c << (r + count * j) << (c + count * k);	//wpisujemy w niego liczby
						tmp = ss.str();										//Tworzymy z niego string
						lista += tmp;										//Dodajemy do wyniku
						lista += old;
					}
					//Je�eli kr�l by� szachowany po ruchu cofnij ruch
					plansza[r][c] = 'B';									//PRzesun go�ca
					plansza[r + count * j][c + count * k] = old;			//Przywr�� figure
														
				}
				count = 1;			//Ustaw odleg�o�� na 1, aby m�c sprawdzic pozosta�e
		}
	}

	return lista;
}

//regu�y ruchu hetmana
std::string Szachy::mozliweQ(int i)
{
	string lista = "";								//(1, -1)  (1, 0)   (1, 1)
	string tmp;										//(0, -1)    Q      (0, 1)
	char old;										//(-1,-1)  (-1, 0)  (-1,1)
	int r = i / 8;
	int c = i % 8;
	int count = 1;

	for (int j = -1; j <= 1; j++) {
		for (int k = -1; k <= 1; k++)
		{
			if (j != 0 || k != 0) {											//Jezeli pole jez rozne od akutalnego
				while (plansza[r + count * j][c + count * k] == ' ' &&		//Tak d�ugo jak puste pole
					(r + count * j) >= 0 && (r + count * j) < 8 &&			//i w planszy
					(c + count * k) >= 0 && (c + count * k) < 8)
				{
					old = plansza[r + count * j][c + count * k];			//zachowaj stara figure
					plansza[r][c] = ' ';									//"Podnies" krolow�
					plansza[r + count * j][c + count * k] = 'Q';			//"Po��" w nowym miejscu
					if (KrolBezpieczny())									//Jezeli ten ruch nie gorzi szachem
					{
						std::stringstream ss;								//tworzymy strumien
						ss << r << c << (r + count * j) << (c + count * k);	//wpisujemy w niego liczby
						tmp = ss.str();										//Tworzymy z niego string
						lista += tmp;										//Dodajemy do wyniku
						lista += old;
					}
					//Je�eli kr�l by� szachowany po ruchu cofnij ruch
					plansza[r][c] = 'Q';									//PRzesun kr�low�
					plansza[r + count * j][c + count * k] = old;			//Przywr�� figure
					count++;												//Przejd� na nast�pne pole
				}
				if (iswlower(plansza[r + count * j][c + count * k]) &&		//Je�eli figura przeciwnika
					(r + count * j) >= 0 && (r + count * j) < 8 &&			//i w planszy
					(c + count * k) >= 0 && (c + count * k) < 8)
				{
					old = plansza[r + count * j][c + count * k];			//zachowaj stara figure
					plansza[r][c] = ' ';									//"Podnies" krolow�
					plansza[r + count * j][c + count * k] = 'Q';			//"Po��" w nowym miejscu
					if (KrolBezpieczny())									//Jezeli ten ruch nie grozi szachem
					{
						std::stringstream ss;								//tworzymy strumien
						ss << r << c << (r + count * j) << (c + count * k);	//wpisujemy w niego liczby
						tmp = ss.str();										//Tworzymy z niego string
						lista += tmp;										//Dodajemy do wyniku
						lista += old;
					}
					//Je�eli kr�l by� szachowany po ruchu cofnij ruch
					plansza[r][c] = 'Q';									//PRzesun kr�lowo�
					plansza[r + count * j][c + count * k] = old;			//Przywr�� figure
													//Ustaw odleg�o�� na 1, aby m�c sprawdzic pozosta�e
				}
				count = 1;
			}
		}
	}

	return lista;
}

//regu�y ruchu kr�la
std::string Szachy::mozliweA(int i)
{
	string lista = "";
	string tmp;
	char old;
	int r = i / 8;
	int c = i % 8;
	for (int j = 0; j < 9; j++)										 //Dla ka�dego pola wok� kr�la
	{
		if (j != 4 && (r - 1 + j / 3) >= 0 && (r - 1 + j / 3) < 8 && //Jezli pozycja jest rozna od tej co zajmuje kr�l
			(c - 1 + j % 3) >= 0 && (c - 1 + j % 3) < 8)			 //oraz nie wychodzi poza tablice
		{
			if (iswlower(plansza[r - 1 + j / 3][c - 1 + j % 3]) ||	//Jezeli te pole zajmuje przeciwnik
				plansza[r - 1 + j / 3][c - 1 + j % 3] == ' ')		//lub jest puste
			{
				old = plansza[r - 1 + j / 3][c - 1 + j % 3];		//Zapamietujemy figure w polu do ktorygo idzie krol
				plansza[r][c] = ' ';								//Ustawiamy aktulana pozycje na pusta
				plansza[r - 1 + j / 3][c - 1 + j % 3] = 'A';		//Przesuwamy kr�la w now� pozycje
				int tmpPoz = PozKrolD;
				PozKrolD = (r - 1 + j / 3) * 8 + (c - 1 + j % 3);	//Uaktualnij pozycje kr�la

				if (KrolBezpieczny())								//Jezeli ruch kt�ry wykonali�my nie nara�a kr�la na szach, 
				{													//to go zapisz
					std::stringstream ss;							//tworzymy strumien
					ss << r << c << (r - 1 + j / 3) << (c - 1 + j % 3);	//wpisujemy w niego liczby
					tmp = ss.str();									//Tworzymy z niego string
					lista += tmp;									//Dodajemy do wyniku
					lista += old;
				}
				//Je�eli kr�l by� szachowany po ruchu cofnij ruch
				plansza[r][c] = 'A';								//PRzesun kr�la
				plansza[r - 1 + j / 3][c - 1 + j % 3] = old;		//Przywr�� figure
				PozKrolD = tmpPoz;									//Przywr�� pozcyje
			}
		}
	}
	//Miejsce na oblsuge roszady


	return lista;
}

bool Szachy::KrolBezpieczny()
{
	//goniec, hetman ukosy
	int count = 1;
	for (int j = -1; j <= 1; j += 2) {											//+=2 pozwala na sprawdzanie jedynie	
		for (int k = -1; k <= 1; k += 2)										//skos�w. Wychodzimy z pozycji kr�la
		{																		//i idziemy po skosach tak dlugo az nie znajdziemy go�ca
			if ((PozKrolD / 8 + count * j) >= 0 && (PozKrolD / 8 + count * j) < 8 &&
				(PozKrolD % 8 + count * k) >= 0 && (PozKrolD % 8 + count * k) < 8) {
				while (plansza[PozKrolD / 8 + count * j][PozKrolD % 8 + count * k] == ' ')	//Do czasu az polne nie jest				
				{
					count++;						//przesuwaj sie
				}
				if (plansza[PozKrolD / 8 + count * j][PozKrolD % 8 + count * k] == 'b' ||	//Jezeli napotkana figura to
					plansza[PozKrolD / 8 + count * j][PozKrolD % 8 + count * k] == 'q')		//goniec lub hetman
				{
					return false;															//to jestesmy szachowani
				}
				count = 1;			//Ustaw odleg�o�� na 1, aby m�c sprawdzic pozosta�e
			}
		}
	}

	//Wie�a, hetman pion i poziom
	count = 1;
	//Pooziom ruch
	for (int j = -1; j <= 1; j += 2) {												
		for (int k = -1; k <= 1; k += 2)										//Wychodzimy z pozycji kr�la
		{																		//i idziemy po poziome tak dlugo az nie znajdziemy figury
			if ((PozKrolD / 8) >= 0 && (PozKrolD / 8) < 8 &&
				(PozKrolD % 8 + count * k) >= 0 && (PozKrolD % 8 + count * k) < 8) {
				while (plansza[PozKrolD / 8][PozKrolD % 8 + count * k] == ' ')	//Do czasu az polne nie jest
				{
					count++;						//przesuwaj sie
				}
				if (plansza[PozKrolD / 8][PozKrolD % 8 + count * k] == 'r' ||	//Jezeli napotkana figura to
					plansza[PozKrolD / 8][PozKrolD % 8 + count * k] == 'q')		//wie�a lub hetman
				{
					return false;															//to jestesmy szachowani
				}
				count = 1;			//Ustaw odleg�o�� na 1, aby m�c sprawdzic pozosta�e
			}
		}
	}
	//Pionowy ruch
	for (int j = -1; j <= 1; j += 2) {												
		for (int k = -1; k <= 1; k += 2)										//Wychodzimy z pozycji kr�la
		{																		//i idziemy po pionie tak dlugo az nie znajdziemy figury
			if ((PozKrolD / 8 + count * k) >= 0 && (PozKrolD / 8 + count * k) < 8 &&
				(PozKrolD % 8) >= 0 && (PozKrolD % 8) < 8) {
				while (plansza[PozKrolD / 8 + count * k][PozKrolD % 8] == ' ')	//Do czasu az polne nie jest
				{
					count++;						//przesuwaj sie
				}
				if (plansza[PozKrolD / 8 + count * k][PozKrolD % 8] == 'r' ||	//Jezeli napotkana figura to
					plansza[PozKrolD / 8 + count * k][PozKrolD % 8] == 'q')		//wie�a lub hetman
				{
					return false;															//to jestesmy szachowani
				}
				count = 1;			//Ustaw odleg�o�� na 1, aby m�c sprawdzic pozosta�e
			}
		}
	}

	//Skoczek
	for (int j = -1; j <= 1; j += 2) {												
		for (int k = -1; k <= 1; k += 2)										//Wychodzimy z pozycji kr�la
		{		
			if (PozKrolD / 8 + j >= 0 && PozKrolD / 8 + j < 8 &&	
				PozKrolD % 8 + 2 * k >= 0 && PozKrolD % 8 + 2 * k < 8) {		//Je�eli jeste�my w planszy
				if (plansza[PozKrolD / 8 + j][PozKrolD % 8 + 2 * k] == 'k')		//Jezeli napotkana figura to
				{																//skoczek
					return false;												//to jestesmy szachowani
				}
			}
			if (PozKrolD / 8 + 2* j >= 0 && PozKrolD / 8 + 2* j < 8 &&
				PozKrolD % 8 + k >= 0 && PozKrolD % 8 + k < 8) {				//Je�eli jeste�my w planszy
				if (plansza[PozKrolD / 8 + 2* j][PozKrolD % 8 + k] == 'k')		//Jezeli napotkana figura to
				{																//skoczek
					return false;												//to jestesmy szachowani
				}
			}
		}
	}

	//Poionek
	if (PozKrolD >= 16)	//Jezeli jestesmy poza drugim rzedem(pionki nie moga byc przed nim)
	{
		if (plansza[PozKrolD / 8  - 1][PozKrolD % 8 - 1] == 'p' &&	//Jezeli w lewym gormyn rogu pionek
			PozKrolD / 8 - 1 >= 0 && PozKrolD / 8 - 1 < 8 &&		//i w planszy
			PozKrolD % 8 - 1 >= 0 && PozKrolD % 8 - 1 < 8)
		{
			return false;											//To jestesmy szachowani
		}
		if (plansza[PozKrolD / 8 - 1][PozKrolD % 8 + 1] == 'p' &&	//Jezeli w prawym gormyn rogu pionek
			PozKrolD / 8 - 1 >= 0 && PozKrolD / 8 - 1 < 8 &&		//i w planszy
			PozKrolD % 8 + 1 >= 0 && PozKrolD % 8 + 1 < 8)
		{
			return false;											//To jestesmy szachowani
		}
	
	}

	//Kr�l
	for (int j = -1; j <= 1; j ++) {
		for (int k = -1; k <= 1; k++)										//Wychodzimy z pozycji kr�la
		{
			if (PozKrolD / 8 + j >= 0 && PozKrolD / 8 + j < 8 &&
				PozKrolD % 8 + k >= 0 && PozKrolD % 8 + k < 8) {				//Je�eli jeste�my w planszy
				if (plansza[PozKrolD / 8 + j][PozKrolD % 8 + k] == 'a')			//Jezeli napotkana figura to
				{																//kr�l
					return false;												//to jestesmy szachowani
				}
			}
		}
	}
	return true;
}

std::string Szachy::AlfaBeta(int glebokosc, int beta, int alfa, int gracz, std::string ruch)
{
	//Format zwr�conych danych: x1y1x2y2figura###############, gdzie "#" symbolizuuja warto�� wyniku
	string lista = this->MozliweRuchy();

	int wartosc;
	if (glebokosc == 0 || lista.empty())	//Je�eli osi�gneli�my odpowiedni poziom rekurencji, lub je�eli nie ma mo�liwych ruch�w(szach)
	{
		std::stringstream ss;				//tworzymy strumien
		ss << this->e.ewaluacja(*this, lista, glebokosc) * (gracz * 2 - 1);		//Ewaluujemy plansze, Jezeli grasz 0 to -1, je�eli 1  to 1, potrzebne to jest ze wzg�du na to,	
		string tmp = ruch;								//�e ruch zawsze wykunujem z perspektywy bia�ych;
		tmp += ss.str();
		return tmp;							//Zachuwjemy format danych i zwracamy
	}
	//Posortuj od najbardziej obiecujacyhc ruch�w do najmniej
	lista = SortujRuchy(lista);

	gracz = 1 - gracz;						//Zmien kolejno��

	for (int i = 0; i < lista.size(); i+=5)		//Dla ka�dego ruchu w li�cie
	{
	this->ZrobRuch(lista.substr(i, 5));		//Wykonujemy ruch
		this->ObrocPlansze();					//Obracamy plansze, tak aby ruch zawsze wykonywa� z perspektywy bia�ych (wolniajesze, ale �atwiejsze w debugowaniu)
	//	this->Print();
		string retString = this->AlfaBeta(glebokosc - 1, beta, alfa, gracz, lista.substr(i, 5));	//Rekurencyjnie idziemy w d�
		wartosc = atoi(retString.substr(5, string::npos).c_str());
		this->ObrocPlansze();					//Obroc jeszcze raz
		this->CofnijRuch(lista.substr(i, 5));	//przyworc plansze

		if (gracz == 0)	//W�ze� minimalizuj�cy (gracz czarny)
		{
			if (wartosc <= beta)
			{
				beta = wartosc;
				if (glebokosc == MakGlebokosc)
				{
					ruch = retString.substr(0, 5);
				}
			}
		}
		else
		{
			if (wartosc > alfa)	//W�ze� maksymalizuj�cy (gracz bia�y)
			{
				alfa = wartosc;
				if (glebokosc == MakGlebokosc)
				{
					ruch = retString.substr(0, 5);
				}
			}
		}
		if (alfa >= beta)	//Warunek odci�cia ga��zi drzewa mozliwych ruch�w (na pewno w tej ga��zi nie bedzie rozwi�zania)
		{
			if (gracz == 0)
			{
				std::stringstream ss;				//tworzymy strumien
				ss << beta;							//Istotny w tym prypadku jest beta
				string tmp = ruch;					//�e ruch zawsze wykunujem z perspektywy bia�ych;
				tmp += ss.str();
				return tmp;							//Zachuwjemy format danych i zwracamy
			}
			else
			{
				std::stringstream ss;				//tworzymy strumien
				ss << alfa;							//Istotny w tym prypadku jest beta
				string tmp = ruch;					//�e ruch zawsze wykunujem z perspektywy bia�ych;
				tmp += ss.str();
				return tmp;							//Zachuwjemy format danych i zwracamy
			}
		}
	}

	if (gracz == 0)							//Rowi�zuje przypadek, gdy nie znajdzemy rowi�zan w powy�szym kodzie
	{
		std::stringstream ss;				//tworzymy strumien
		ss << beta;							//Istotny w tym prypadku jest beta
		string tmp = ruch;					//�e ruch zawsze wykunujem z perspektywy bia�ych;
		tmp += ss.str();
		return tmp;							//Zachuwjemy format danych i zwracamy
	}
	else
	{
		std::stringstream ss;				//tworzymy strumien
		ss << alfa;							//Istotny w tym prypadku jest beta
		string tmp = ruch;					//�e ruch zawsze wykunujem z perspektywy bia�ych;
		tmp += ss.str();
		return tmp;							//Zachuwjemy format danych i zwracamy
	}
}


void Szachy::ObrocPlansze()
{
	char temp;
	int r, c;
	bool poczatek = false;

	for (int i = 0; i < 32; i++)	//Dla pierwszej po�owy tablicy
	{
		r = i / 8; c = i % 8;
		if (iswupper(plansza[r][c]))	//Jezeli aktualna literka jest duza
		{
			temp = towlower(plansza[r][c]); //to zapami�taj j� jako ma��
		}else
		{
			temp = towupper(plansza[r][c]); //to zapami�taj j� jako du��
		}
		if (iswupper(plansza[7-r][7-c]))	//Jezeli przeciwna literka jest duza
		{
			plansza[r][c] = towlower(plansza[7-r][7-c]); //to zamie� z aktualn�
		}
		else
		{
			plansza[r][c] = towupper(plansza[7-r][7-c]); //to zamie� z aktualn�
		}
		plansza[7 - r][7 - c] = temp;		//Zamie� przeciwn�
	}

	int Kroltemp = PozKrolD;		//Zapami�taj pozycje bia�ego
	PozKrolD = 63 - PozKrolM;		//Ustaw pozycje bialego na przeciwn�
	PozKrolM = 63 - Kroltemp;		//Uwstaw pozycje czarnego na przeciwn�
}


Szachy::Szachy()
{
	while (plansza[PozKrolD / 8][PozKrolD % 8] != 'A') {
//		std::cout << plansza[i / 8][i % 8] << std::endl;
		PozKrolD++;
	}
	while (plansza[PozKrolM / 8][PozKrolM % 8] != 'a') {
//		std::cout << plansza[i / 8][i % 8] << std::endl;
		PozKrolM++; 
	}

//	std::cout << "Bialy: " << PozKrolD << std::endl;
//	std::cout << "Czarny: " << PozKrolM << std::endl;
}


std::string Szachy::SortujRuchy(std::string lista)
{
	int rozmiar = lista.size() / 5;		//Tyle istnieje ruchow w liscie
	int *wyniki = new int[rozmiar];		//stworzenie tablicy
	for (int i = 0; i < lista.size(); i += 5)
	{
		ZrobRuch(lista.substr(i, 5));				//Zrob ruch
		wyniki[i / 5] = -e.ewaluacja(*this, "", 0);	//ocen plansze
		CofnijRuch(lista.substr(i, 5));				//cofnij ruch
	}
	std::string posortowana ="", start = lista;

	for (int i = 0; i < fmin(6, rozmiar); ++i)	//We� 6 najlepszych lub tyle jak dluga jest lista
	{
		int max = -1000000;
		int maxPoz = 0;
	
		for (int j = 0; j < rozmiar; j++)
		{
			if (wyniki[j] > max)	//Znajd� najwi�szy
			{
				max = wyniki[j];
				maxPoz = j;
			}
		}
		wyniki[maxPoz] = -1000000;					//Ustaw na bardzo maly by poszukac nastepnej najwiekszej
		posortowana += lista.substr(maxPoz * 5, 5); //Dodaj do posortowyanych dany ruch
		size_t a = start.find(lista.substr(maxPoz * 5, 5));
		start.replace(a, 5, "");					//Usun ruch z poczotkowej listy
	}



	delete[] wyniki;
	return posortowana + start;
}