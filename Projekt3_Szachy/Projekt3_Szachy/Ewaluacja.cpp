#include "Szachy.h"

int Szachy::Ewaluacja::ewaluacja(Szachy  &s, std::string lista, int glebokosc)
{
	int figura = ewaluacjaFigury(s);
	int wynik = 0;	//Dodaj wartoœci jednej strony
	wynik += ewaluacjaAtaku(s);
	wynik += figura;
	wynik += ewaluacjaMobinosci(s, lista.size() / 5, glebokosc);
	wynik += ewaluacjaPozycji(s, figura);

	//Odejmnij wartoœci drugiej strony
	s.ObrocPlansze();
	figura = ewaluacjaFigury(s);
	wynik -= ewaluacjaAtaku(s);
	wynik -= figura;
	wynik -= ewaluacjaMobinosci(s, lista.size() / 5, glebokosc);
	wynik -= ewaluacjaPozycji(s, figura);
	s.ObrocPlansze();

	return -(wynik + glebokosc*50);			//wynik musi byc ujemny bo ewalujemy z strony czarnego, wyniki g³ebiej w drzewie sa berdzeij wartosciowe
}

int Szachy::Ewaluacja::ewaluacjaAtaku(Szachy  &s )
{
	int wynik = 0;
	int tmp = s.GetPosKrolD();

	for (int i = 0; i < 64; ++i)
	{
		//Przyjêto standardowe wartoœæ pionków * 100
		switch (s(i / 8, i % 8))
		{
		case 'P':
		{
			s.SetPosKrolD(i); //umieœæ króla w miejsce pionka
			if (!s.KrolBezpieczny()) //Jezeli nie jest bezpieczy to pionek jest atakowany
			{
				wynik -= 100;
			}
		}
			break;
		case 'R':
		{
			s.SetPosKrolD(i); //umieœæ króla w miejsce wierzy
			if (!s.KrolBezpieczny()) //Jezeli nie jest bezpieczy to pionek jest atakowany
			{
				wynik -= 500;
			}
		}
			break;
		case 'K':
		{
			s.SetPosKrolD(i); //umieœæ króla w miejsce skoczka
			if (!s.KrolBezpieczny()) //Jezeli nie jest bezpieczy to pionek jest atakowany
			{
				wynik -= 300;
			}
		}
			break;
		case 'B':
		{
			s.SetPosKrolD(i); //umieœæ króla w miejsce gonca
			if (!s.KrolBezpieczny()) //Jezeli nie jest bezpieczy to pionek jest atakowany
			{
				wynik -= 300;
			}
		}
			break;
		case 'Q':
		{
			s.SetPosKrolD(i); //umieœæ króla w miejsce hetmana
			if (!s.KrolBezpieczny()) //Jezeli nie jest bezpieczy to pionek jest atakowany
			{
				wynik -= 900;
			}
		}
			break;
		default:
			break;
		}
	}
	s.SetPosKrolD(tmp);

	if (!s.KrolBezpieczny())	//Duza kara jezeli twoj krol jest atakowany
		wynik -= 1000;

	return wynik / 2; //Jako, ¿e atakowanie jest jest równie dobre co zbijanie, to zmniejsz jest wage o polowe
}

int Szachy::Ewaluacja::ewaluacjaFigury(Szachy  &s )
{
	int wynik = 0;
	int iloscGoncow = 0;

	for(int i=0; i<64; ++i)
	{
		//Przyjêto standardowe wartoœæ pionków * 100
		switch (s(i/8, i%8))
		{
		case 'P':
			wynik += 100;
			break;
		case 'R':
			wynik += 500;
			break;
		case 'K':
			wynik += 300;
			break;
		case 'B':
			iloscGoncow ++;
			break;
		case 'Q':
			wynik += 900;
			break;
		default:
			break;
		}
	}
	if (iloscGoncow >= 2)		//W sytuacji gdy mamy wiêcej ni¿ dwa goñce s¹ one wiescej warte
	{
		wynik += 300 * iloscGoncow;
	}
	else
	{
		if (iloscGoncow == 1)	//Gdy mamy tylko 1 goñca jest on mniej warty
		{
			wynik += 250;
		}
	}

	return wynik;
}

int Szachy::Ewaluacja::ewaluacjaMobinosci(Szachy  &s, int ilosRuchow, int glebokosc)
{
	int wynik = 0;

	wynik += ilosRuchow * 5; //5 im wiecej ruchow tym lepiej, kazdy ruch ma wage 5;

	if (ilosRuchow == 0)  //Szach albo pat
	{
		if (!s.KrolBezpieczny())		//Jezeli krol jest zagrozony, to szach
			wynik += -200000 * glebokosc;	//Szach jest gorszy od patu
		else
			wynik += -150000 * glebokosc;
	}

	return -1;
}

int Szachy::Ewaluacja::ewaluacjaPozycji(Szachy  &s, int figura)
{
	int wynik = 0;

	for (int i = 0; i < 64; ++i)
	{
		//Przyjêto standardowe wartoœæ pionków * 100
		switch (s(i / 8, i % 8))
		{
		case 'P':
			wynik += pionekTab[i/8][i%8];
			break;
		case 'R':
			wynik += wierzaTab[i / 8][i % 8];
			break;
		case 'K':
			wynik += skoczekTab[i / 8][i % 8];
			break;
		case 'B':
			wynik += goniecTab[i / 8][i % 8];
			break;
		case 'Q':
			wynik += hetmanTab[i / 8][i % 8];
			break;
		case 'A':
		{
			if (figura >= 1700)		//Jezeli na planszy s¹ co najmniej wszystkie pionki i hetman
				wynik += krolMidTab[i / 8][i % 8];
			else
				wynik += krolEndTab[i / 8][i % 8];
		}
		default:
			break;
		}
	}

	return wynik;
}