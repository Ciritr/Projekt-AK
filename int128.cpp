#include "stdafx.h"
#include "int128.h"


int128::int128()
{
	for (int i = 0; i < 8192; i++)
	{
		tab[i] = 0;
		temp[i] = 0;
	}
	przeniesieniesumy = 0;
}
int128::~int128()
{

}
void int128::StringToBin()
{
	string bufor, sciezka;
	system("CLS");
	cout << "Podaj ścieżkę pliku." << endl;
	cin >> sciezka;
	//system("CLS");
	//sciezka = "d:/l.txt";
	fstream plik(sciezka.c_str(), ios::in);
	getline(plik, bufor);
	plik.close();
	//system("CLS");
	strcpy(tabchar, bufor.c_str());
	cout << tabchar << endl;
	przecinek = 0;
	if (tabchar[0] == '-')
	{
		znak = 1;
		for (int i = 0; i < 2047; i++)
		{
			tabchar[i] = tabchar[i + 1];
		}
		tabchar[2047] = '0';
	}
	else
	{
		znak = 0;
	}
	for (int i = 0; i < 2048; i++)
	{
		if (tabchar[i] == '.')
		{
			przecinek = i + 1;					//przecinek jest na 3 pozycji
			break;
		}
	}
	//cout << przecinek << endl;
	cin.ignore();
	//----------------------------------CAŁKOWITA-------------------------------------
	int128 temp1;
	int k = 0;
	int potega = 0;
	for (int i = przecinek - 2; i >= 0; i--)
	{
		int tablicareszt[4] = { 0 };
		temp1.tab[0] = tabchar[i] - '0';
		int c = 0;
		do
		{
			int reszta = temp1.tab[0] % 2;
			tablicareszt[c] = reszta;
			temp1.tab[0] /= 2;
			c++;

		} while (temp1.tab[0] != 0);
		int128 temporary;
		for (int i = 0; i < 4; i++)
		{
			temporary.tab[i] = tablicareszt[i];
		}
		x10(temporary, potega);
		potega++;
	}
	//------------------------------------UŁAMEK----------------------------------------
}
int128 int128::Dodaj(int128 t1, int128 t2)
{
	for (int i = 0; i < 8192; i++)
	{
		if (t1.tab[i] == 2)
		{
			t1.tab[i] = 0;
			t1.tab[i + 1]++;
		}
		if (t1.tab[i] == 0 && t2.tab[i] == 0)
		{
			t1.tab[i] = 0;
		}
		else if (t1.tab[i] == 0 && t2.tab[i] == 1)
		{
			t1.tab[i] = 1;
		}
		else if (t1.tab[i] == 1 && t2.tab[i] == 0)
		{
			t1.tab[i] = 1;
		}
		else if (t1.tab[i] == 1 && t2.tab[i] == 1)
		{
			t1.tab[i] = 0;
			t1.tab[i + 1]++;
		}
	}
	return t1;
}
void int128::x10(int128 wynik, int ile)
{
	if (ile == 0)
	{
		DodajDoTaba(wynik);
	}
	else
	{
		for (int i = 0; i < ile; i++)
		{
			wynik = PrawdziweX10(wynik);
		}
		DodajDoTaba(wynik);
	}
}
void int128::DodajDoTaba(int128 t1)
{
	for (int i = 0; i < 8192; i++)
	{
		if (tab[i] == 2)
		{
			tab[i] = 0;
			tab[i + 1]++;
		}
		if (tab[i] == 0 && t1.tab[i] == 0)
		{
			tab[i] = 0;
		}
		else if (tab[i] == 0 && t1.tab[i] == 1)
		{
			tab[i] = 1;
		}
		else if (tab[i] == 1 && t1.tab[i] == 0)
		{
			tab[i] = 1;
		}
		else if (tab[i] == 1 && t1.tab[i] == 1)
		{
			tab[i] = 0;
			tab[i + 1]++;
		}
	}
}
int128 int128::PrawdziweX10(int128 wynik)
{
	int128 temp1, temp2;
	temp1 = temp2 = wynik;
	for (int i = 8191; i > 0; i--)
	{
		temp1.tab[i] = temp1.tab[i - 1];
	}
	temp1.tab[0] = 0;
	for (int i = 8191; i > 2; i--)
	{
		temp2.tab[i] = temp2.tab[i - 3];
	}
	temp2.tab[0] = 0;
	temp2.tab[1] = 0;
	temp2.tab[2] = 0;
	wynik = Dodaj(temp1, temp2);
	return wynik;
}
void int128::p10(int128 wynik, int ile)
{
	if (ile == 1)
	{
		DodajDoTempa(wynik);
	}
	else
	{
		for (int i = 0; i < ile; i++)
		{
			wynik = PrawdziweP10(wynik);
		}
		DodajDoTempa(wynik);
	}
}
int128 int128::PrawdziweP10(int128 wynik)
{
	int128 temp1, temp2;
	temp1 = temp2 = wynik;
	for (int i = 8191; i > 0; i--)
	{
		temp1.temp[i] = temp1.temp[i - 1];
	}
	temp1.temp[0] = 0;
	for (int i = 8191; i > 2; i--)
	{
		temp2.temp[i] = temp2.temp[i - 3];
	}
	temp2.temp[0] = 0;
	temp2.temp[1] = 0;
	temp2.temp[2] = 0;
	wynik = DodajT(temp1, temp2);
	return wynik;
}
void int128::DodajDoTempa(int128 t1)
{
	for (int i = 8191; i >= 0; i--)
	{
		if (temp[i] == 2)
		{
			temp[i] = 0;
			temp[i - 1]++;
		}
		if (temp[i] == 0 && t1.temp[i] == 0)
		{
			temp[i] = 0;
		}
		else if (temp[i] == 0 && t1.temp[i] == 1)
		{
			temp[i] = 1;
		}
		else if (temp[i] == 1 && t1.temp[i] == 0)
		{
			temp[i] = 1;
		}
		else if (temp[i] == 1 && t1.temp[i] == 1)
		{
			temp[i] = 0;
			temp[i - 1]++;
		}
	}
}
int128 int128::DodajT(int128 t1, int128 t2)
{
	for (int i = 8191; i >= 0; i--)
	{
		if (t1.temp[i] == 2)
		{
			t1.temp[i] = 0;
			t1.temp[i - 1]++;
		}
		if (t1.temp[i] == 0 && t2.temp[i] == 0)
		{
			t1.temp[i] = 0;
		}
		else if (t1.temp[i] == 0 && t2.temp[i] == 1)
		{
			t1.temp[i] = 1;
		}
		else if (t1.temp[i] == 1 && t2.temp[i] == 0)
		{
			t1.temp[i] = 1;
		}
		else if (t1.temp[i] == 1 && t2.temp[i] == 1)
		{
			t1.temp[i] = 0;
			t1.temp[i - 1]++;
		}
	}
	return t1;
}
void int128::Ulamek()							//zamiana ułamka na binarny
{
	int przecinek_binarny = 0;					//ta zmienna będzie odpowiadała w którym miejscu ma się znaleźć przecinek w liczbie binarnej
	for (int i = 8191; i >= 0; i--)				//od końca przeszukuję tablicę w poszukiwaniu pierwszej jedynki, która jest pierwszą cyfrą liczby całkowitej
	{											//tak, liczba całkowita jest zapisywana od tyłu
		if (tab[i] == 1)						//jeśli ją znajdę, to znaczy że od tego miejsca będę mogła ustawiać przecinek
		{
			przecinek_binarny = i + 1;
			break;
		}
	}
	//cout << przecinek_binarny << endl;
	int siterator = 0;							//siterator będzie oznaczał miejsce końca ułamka
	for (int i = przecinek + 1; i < 2047; i++)	//od przecinka dziesiętnego szukam końca tablicy
	{
		if (tabchar[i] < '0' || tabchar[i] > '9')//jeśli trafię na inny znak niż cyfra, to oznacza, że ułamek się skończył
		{
			siterator = i;						//oznaczam miejsce
			break;								//wychodzę z pętli
		}
	}
	short int supertablica[2048];				//w tej tablicy będzie przechowywany cały ułamek. Nie będzie miał więcej jak 2048, bo takie jest wejście
	int rozmiar_tablicy = 0;					//chcę wiedzieć jak długi jest ułamek
	for (int i = przecinek; i < siterator; i++)	//od miejsca przecinka do końca ułamka
	{
		supertablica[rozmiar_tablicy] = tabchar[i] - '0';//spisuję cyfry do nowej tablicy odejmując kod ascii w którym były zapisane
		rozmiar_tablicy++;						//zwiększam rozmiar tablicy
	}
	zero=0;										//tego chciałabym się pozbyć, ale musiałabym inaczej zmieniać ułamek z powrotem na dziesiętny
	for (int i=0; i<rozmiar_tablicy; i++)
	{
		if (supertablica[i] !=0)
		{
			if (supertablica[i-1]==0 && supertablica[i] == 1 && supertablica[i+1] == 0)
				zero++;
			break;
		}
		zero++;
	}
	//cout << zero << endl;
	int wysw = siterator - przecinek;						//ta zmienna pokazuje ile mam miejsc międz przecinkiem a końcem ułamka
	//------------MOJA PRÓBA-------------------------
	/*cout << endl;
	cout << siterator << endl;
	cout << przecinek << endl;								//Dlaczego 3?    trzecia pozycja w tablicy, ale ideks 2
	cout << wysw << endl;
	cout << endl;*/
	//-----------KONIEC------------
	int twysw, przeniesienie = 0, k = 0;					
	/*for (int i = 0; i < wysw; i++)
	{
	cout << supertablica[i];
	}
	cout << endl;
	//------------MOJA PRÓBA-------------------------
	cout << endl;
	cout << przecinek_binarny << endl;
	cout << endl;
	//-----------KONIEC------------
	cout << przecinek_binarny << endl;*/
	for (int i = 8192 - przecinek_binarny; i >= 0; i--) // od przecinka binarnego mogę wstawiać kolejne znaki ułamka
	{
		twysw = wysw - 1;								//
		for (int j = wysw - 1; j >= 0; j--)				//muszę całą tablicę pomnożyć przez dwa według schematu hornera
		{
			if (j == 0)									//jeśli jestem już na początku tablicy
			{
				supertablica[0] *= 2;					//to mnoże zawartość pierwszej komórki przez 2
				if (supertablica[twysw + 1] >= 10)		//jeśli w poprzedniej komórce było dziesięć lub więcej
				{
					supertablica[twysw]++;				//to do zawartości tej komórki dodaję 1
					supertablica[twysw + 1] -= 10;		//a od poprzedniej odejmuję 10
				}
				if (supertablica[0] >= 10)				//jak tu jest więcej jak dziesięć, znacz przed przecinkiem będzie 1
				{										//spisane do ułamka
					przeniesienie++;					//zaznaczam to przeniesieniem
					supertablica[0] -= 10;				//a tu odejmuję 10
				}
			}
			else										//dla każdej innej komórki oprócz pierwszej
			{
				supertablica[twysw] *= 2;				//mnożę zawartość przez 2
				if (supertablica[twysw + 1] >= 10)		//sprawdzam, czy powinno być przeniesienie z poprzedniej komórki
				{
					supertablica[twysw]++;
					supertablica[twysw + 1] -= 10;
				}
				twysw--;
			}
		}
		if (przeniesienie)								//jeśli było przeniesienie
		{
			temp[k] = 1;								//to w temp, czyli tablicy na ułamek binarny wstaw 1
			k++;										//przesuń się na kolejną pozycję
		}
		else
		{
			temp[k] = 0;								//jeśli przed przecinkiem było zero, to je wstaw
			k++;										//i przesuń się na kolejną pozycję
		}
		przeniesienie = 0;								//wyzeruj przeniesienie
	}
	//cout << wysw << endl;
	//--------------------------------WYŚWIETLANIE--------------------------------------
	/*for (int i = 0; i < 40; i++)
	{
	cout << tab[i];
	}
	cout << endl;
	for (int i = 0; i < 40; i++)
	{
	cout << temp[i];
	}
	cout << endl;*/
	//cout << "Liczba binarnie wygląda: " << endl;
	int f = 0;											//a teraz zapiszę to do jednej tablicy
	for (int j = przecinek_binarny - 1; j >= 0; j--)	//najpierw liczbę całkowitą
	{
		wynikbinarnie[f] = tab[j];
		//cout << wynikbinarnie[f];
		f++;
	}
	f = 0;
	//cout << ",";
	for (int i = przecinek_binarny; i<8192; i++)		//a resztę miejsc wypełnię ułamkiem
	{
		wynikbinarnie[i] = temp[f];
		//cout << wynikbinarnie[i];
		f++;
	}
	//cout << endl;
	int potega = 0;										//teraz do wykładnika potrzebuję policzyć potęgę
	if (przecinek_binarny>1)							//jeśli przecinek binarny jest większy od 1 znaczy, że istnieje jakaś część całkowita
	{
		potega = przecinek_binarny;						//i potęga będzie taka ile jest miejsc przed przecinkiem
		//cout << potega << endl;
	}
	else if (przecinek_binarny == 1)					//jeśli przecinek jest równy 1 oznacza to, że liczba wygląda 1,coś, czyli potęga jest równa 0
		potega = 0;
	else if (przecinek_binarny == 0)					//jeśli przecinek binarny jest równy 0, to znaczy, że potęgę trzeba liczyć wstecz, bo liczba
	{													//wygląda 0,coś. tyle ile zer jest od przecinka do pierwszej jedynki w cosiu, taka będzie ujemna potęga
		for (int j = 0; j<8192; j++)					
		{
			if (wynikbinarnie[j] == 1)					//więc szukam jedynki
			{
				potega = 0 - j - 1;						//ilosc zer w zapisie liczby binarniej do pierwszej jednyki świadczy o potędze liczby
				//cout << potega << endl;
				break;
			}
		}
	}
	//cout << potega << endl;
	//--------------------------WYKŁADNIK-------------------------------
	wykladnik[0] = 1;												//pierwszą cyfrą wykładnika będzie 1
	for (int i = 1; i<15; i++)
	{
		wykladnik[i] = 0;											//całą resztę wypełniam zerami
	}																//bo domyślą potęgę chcę ustawić równą 1
	int obciazenie[15];												
	if (potega<0)													//dla ujemnych potęg 0.0000000cos
	{
		for (int i = 0; i<15; i++)									//zeruję obciążenie
		{
			obciazenie[i] = 0;
		}
		int p = abs(potega);										//pod zmienną p zapisuję wartość bezwzględną z potęgi
		int c = 0;
		do
		{
			obciazenie[c] = p % 2;									//i do obciążenia wkładam binarną wartość potęgi
			p /= 2;													//reszta z dzielenia przez 2 zapisywana jest do tablicy
			c++;													//potęga jest dzielona przez 2
		} while (p != 0);
		for (int i = 0; i<15; i++)									//teraz odwracam wartość obciążenia
		{
			if (obciazenie[i] == 1)									//w miejsce każdej jedynki wstawiam 0
				obciazenie[i] = 0;
			else
				obciazenie[i] = 1;									//w każde zero wstawiam 1
		}
		wykladnik[0] = 0;											//zeruję pierwszą cyfrę wykładnika
		for (int i = 1; i<15; i++)
		{
			wykladnik[i] = 1;										//resztę wypełniam jedynkami
		}
		int u = 0;
		for (int i = 14; i>0; i--)									//a teraz wstawiam potęgę
		{
			wykladnik[i] = obciazenie[u];
			u++;
		}
	}
	else if (potega == 0)						//dla zerowej potęgi, w przypadku 1,cos
	{
		wykladnik[0] = 0;						//dla potęgi zerowej jest tylko jeden możliwy wykładnik pierwsze 0, reszta 1
		for (int i = 1; i<15; i++)
		{
			wykladnik[i] = 1;
		}
	}
	else if (potega >= 1)									//dla normalnych liczb
	{
		for (int i = 0; i<15; i++)							//jak wcześniej - zeruję obciążenie
		{
			obciazenie[i] = 0;
		}
		int p = potega - 2;									//potęga jest o dwa za duża, bo policzyłam przecinek, a wartość binarna obciążenia
		int c = 0;											//będzie o jeden mniejsza od rzeczywistej wartości
		do
		{
			obciazenie[c] = p % 2;							//zamieniam na binarny
			p /= 2;
			c++;
		} while (p != 0);
		wykladnik[0] = 1;									//pierwsze miejsce jest równe 0
		int u = 0;
		for (int i = 14; i>0; i--)
		{
			wykladnik[i] = obciazenie[u];					//resztę wypełniam potęgą
			u++;
		}
	}
	//--------------------------MANTYSA-----------------------------------
	if (potega >= 0)										//jeśli potęga jest większa, równa 0
	{
		for (int i = 0; i<4080; i++)						//to mantysę wypełniam zerami i jedynkami zapisanymi w tablicy wynikbinarnie
		{													//oczywiście, pierwsza jedynka znika
			mantysa[i] = wynikbinarnie[i + 1];
		}
	}
	else													//w przeciwnym wypadku
	{
		for (int i = 0; i<4080; i++)
		{
			mantysa[i] = wynikbinarnie[i - potega];			//pomijam jeszcze te wszystkie zera aż się dostanę do pierwszej jedynki
		}
	}
	//----------------------WYŚWIETLANIE---------------------------------
	cout << "Liczba przekonwertowana IEEE 754 z obciążeniem 2^14-1: " << endl;
	cout << znak << " ";
	for (int i = 0; i<15; i++)
		cout << wykladnik[i];
	cout << " ";
	for (int i = 0; i<4080; i++)
		cout << mantysa[i];
	cout << endl;//*/
}
void int128::BintoDec()
{
	char z;
	string liczba;
	int rozmiar = 1;
	int pozycja = 0;
	short int *binpotega = new short int[rozmiar];						//tablica dynamiczna
	if (znak == 1)														//zczytywanie znaku
		z = '-';
	long double potegaDwojki = 0;
	if (wykladnik[0] == 0)													//dla ujemnych potęg 0.0000000cos
	{
		//#pragma omp parallel
		//#pragma omp for schedule (dynamic,1) 
		for (int i = 1; i<15; i++)										//pomiń wszystkie jednyki w wykładniku
		{			
			if (wykladnik[i] == 0)										//do czasu pojawienia się zera
			{
				pozycja = 15 - i - 1;									//zaznacz pozycję i rozmiar tego miejsca
				rozmiar = 15 - i;
				break;
			}
		}
		//cout << rozmiar << endl << pozycja << endl << endl;
		for (int i = 15 - rozmiar; i <= 15; i++)					//do tabeli dynamicznej zczytaj tyle wykładnika ile będzie to konieczne,
		{															//czyli od rozmiaru do końca
			binpotega[pozycja] = wykladnik[i];
			//cout << wykladnik[i] << endl;
			//cout << binpotega[pozycja];
			pozycja--;												//zmniejszaj także pozycję
		}
		//cout << endl;
		for (int i = 0; i<rozmiar; i++)								//teraz zamień jedynki na zera, a zera na jedynki
		{
			if (binpotega[i] == 0)
			{
				binpotega[i] = 1;
			}
			else
			{
				binpotega[i] = 0;
			}
			//cout << binpotega[i];
		}
		//cout << endl;
		for (int i = 0; i <rozmiar; i++)					//policz ile dziesiętnie wynosi potęga
		{
			if (binpotega[i] == 1)							//czyli w miejscu jedynek
				potegaDwojki = potegaDwojki + pow(2.0, i);
		}
		potegaDwojki = 0 - potegaDwojki;					//potęga jest ujemna, więc trzeba jej policzoną wartość odjąć od zera
		//cout << potegaDwojki << endl;
	}
	else if (wykladnik[0] == 1)						//na końcu zamiany na potęgę trzeba dodać 1!
	{
		for (int i = 1; i<15; i++)					//jeśli potęga jest dodatnia kroki postępowania są bardzo podobne
		{											//z tym, że nie zmieniam jedynek na zera, a zer na jedynki
			if (wykladnik[i] == 1)
			{
				pozycja = 15 - i - 1;
				rozmiar = 15 - i;
				break;
			}
		}
		//cout << rozmiar << endl << pozycja << endl << endl;
		for (int i = 15 - rozmiar; i <= 15; i++)
		{
			binpotega[pozycja] = wykladnik[i];
			//cout << wykladnik[i] << endl;
			//cout << binpotega[pozycja];
			pozycja--;
		}
		//cout << endl;
		/*for (int i = 0; i<rozmiar; i++)
		{
		cout << binpotega[i];
		}*/
		//cout << endl;
		for (int i = 0; i <rozmiar; i++)
		{
			if (binpotega[i] == 1)
				potegaDwojki = potegaDwojki + pow(2.0, i);
		}
		potegaDwojki++;							//to z tego tam na początku
		//cout << potegaDwojki << endl;
	}
	calosc[0] = 1;												//wstawiam ukrytą jedynkę
	for (int i = 0; i<4080; i++)								//resztę wypełniam mantysą
	{
		calosc[i + 1] = mantysa[i];
	}
	int rozmiarCalkowita = 0;									//potrzebuję znać rozmiar liczby całkowitej 
	int rozmiarUlamek = 0;										//i ułamka
	if (potegaDwojki>0)
	{
		rozmiarCalkowita = potegaDwojki + 1;					//część całkowita będzie miała tyle miejsc jaka jest wartość potęgi dwójki
		rozmiarUlamek = 4081 - potegaDwojki;					//reszta zajmie ułamek
	}
	else
	{
		rozmiarUlamek = 4080 + abs(potegaDwojki);				//w przeciwnym wypadku ułamek musi mieć tyle miejsca ile jest w mantysie + wartość potęgi dwójki
	}
	short int *calkowita = new short int[rozmiarCalkowita];		//kolejne dwie tablice dynamiczne - na część całkowitą
	short int *ulamek = new short int[rozmiarUlamek];			//i ułamkową
	//cout << rozmiarCalkowita << " " << rozmiarUlamek << endl;
	//cin.ignore();
	rozmiarUlamek=rozmiarUlamek-1;								
	int iloscZer = abs(potegaDwojki) - 1;						//to mi potrzebne do tego, by ułamek wypełnić zerami
	if (potegaDwojki>0)											//dla potęgi większej od zera
	{
		for (int i = 0; i<rozmiarCalkowita; i++)				//tyle zapisz z całości część całkowitą
		{
			calkowita[i] = calosc[i];
			//cout << calkowita[i];
		}
		//cout << ",";
		for (int i = rozmiarCalkowita; i<rozmiarUlamek+rozmiarCalkowita; i++)
		{
			ulamek[i - rozmiarCalkowita] = calosc[i];			//resztę zapisz do ułamka
		}
		/*for (int i = 0; i<rozmiarUlamek; i++)
		{
			cout << ulamek[i];
		}
		cout << endl;
		cout << rozmiarUlamek << endl;*/
	}
	else if (potegaDwojki == 0)									//gdy potęga jest równa zero
	{
		rozmiarCalkowita = 1;									//to w części całkowitej będzie tylko 1
		calkowita[0] = 1;
		//cout << calkowita[0] << ",";
		for (int i = 0; i<rozmiarUlamek; i++)					//a część ułamkową trzeba wypełnić zerami
		{
			ulamek[i] = calosc[i - iloscZer];
			//cout << ulamek[i];
		}
	}
	else														//potęga mniejsza od zera
	{
		//cout << "0,";											//całość będzie równa 0
		for (int i = 0; i<iloscZer; i++)						//trzeba uzupełnić zera
		{
			ulamek[i] = 0;
			//cout << ulamek[i];
		}
		for (int i = iloscZer; i<rozmiarUlamek; i++)			//i spisać całą resztę ułamku
		{
			ulamek[i] = calosc[i - iloscZer];
			//cout << ulamek[i];
		}

	}
	//cout << iloscZer << endl;
	//cin.ignore();
	//------------Tu nastąpi przerobienie na stringa części całkowitej----------------
	//cout << endl;
	char *tablicaBitow = new char[rozmiarCalkowita + 1];		//teraz zamieniam tablicę liczbową
	for (int i = 0; i<rozmiarCalkowita; i++)					//na tablicę znaków
	{
		tablicaBitow[i] = calkowita[i] + '0';
	}
	/*for(int i = 0; i<rozmiarCalkowita; i++)
	{
	cout << tablicaBitow[i];
	}
	cout << endl;*/
	string bitowaCalosc;
	for (int i = 0; i<rozmiarCalkowita; i++)
	{
		bitowaCalosc = bitowaCalosc + tablicaBitow[i];			//i wpisuję to do stringa
	}
	//cout << bitowaCalosc << endl;
	string dziesietnaCalosc;									//tu będzie wpisywany wynik już dziesiętnie
	int licznik1, cyfraBinarna, przeniesienie, schemat;
	cout << endl;
	dziesietnaCalosc = "0"; licznik1 = 0;						//na początku jest krótka
	while ((licznik1 < bitowaCalosc.length()) && ((bitowaCalosc[licznik1] == '0') || (bitowaCalosc[licznik1] == '1')))
	{				//do póki się nie skończy i są w niej zera lub jedynki
		przeniesienie = 0;									// Przeniesienie na początku jest równe 0
		cyfraBinarna = bitowaCalosc[licznik1] - 48;			// Cyfra binarna
		for (int j = dziesietnaCalosc.length() - 1; j >= 0; j--)
		{													// Schemat Hornera
			schemat = 2 * (dziesietnaCalosc[j] - 48) + cyfraBinarna + przeniesienie;
			cyfraBinarna = 0;									// Wyznaczamy przeniesienie do następnej kolumny
			przeniesienie = schemat / 10;						// Cyfrę wynikową zapisujemy w miejscu docelowym
			dziesietnaCalosc[j] = (char)((schemat % 10) + 48);
			// Jeśli po wyczerpaniu cyfr dziesietnaCalosc przeniesienie ma wartość
			// większą od zera, to jest ono równe pierwszej cyfrze
			if (!j && przeniesienie) dziesietnaCalosc = (char)(przeniesienie + 48) + dziesietnaCalosc;
		};													// Następna cyfra binarna
		licznik1++;
	};
	//delete calkowita;
	//------------------------A tu miejsce na konwersję przecinka;
	char *tablicaUlamkow = new char[rozmiarUlamek - rozmiarCalkowita];
	for (int i = 0; i<rozmiarUlamek; i++)					//teraz to samo z ułamkiem
	{
		tablicaUlamkow[i] = ulamek[i] + '0';
	}																	//tu się pojawia problem, liczba jest za duża i jest przeładowanie stosu
	/*for(int i = 0; i<rozmiarUlamek; i++)
	{
	cout << tablicaUlamkow[i];
	}
	cout << endl;*/
	string bitowyUlamek;
	for (int i = 0; i<rozmiarUlamek; i++)
	{
		bitowyUlamek = bitowyUlamek + tablicaUlamkow[i];
	}
	//cout << bitowyUlamek << endl;
	string dziesietnyUlamek;
	licznik1, cyfraBinarna, przeniesienie, schemat = 0;
	cout << endl;
	dziesietnyUlamek = "0"; licznik1 = 0;
	while ((licznik1 < bitowyUlamek.length()) && ((bitowyUlamek[licznik1] == '0') || (bitowyUlamek[licznik1] == '1')))
	{
		przeniesienie = 0;									// Przeniesienie
		cyfraBinarna = bitowyUlamek[licznik1] - 48;			// Cyfra binarna
		for (int j = dziesietnyUlamek.length() - 1; j >= 0; j--)
		{													// Schemat Hornera
			schemat = 2 * (dziesietnyUlamek[j] - 48) + cyfraBinarna + przeniesienie;
			cyfraBinarna = 0;									// Wyznaczamy przeniesienie do następnej kolumny
			przeniesienie = schemat / 10;						// Cyfrę wynikową zapisujemy w miejscu docelowym
			dziesietnyUlamek[j] = (char)((schemat % 10) + 48);
			// Jeśli po wyczerpaniu cyfr dziesietnyUlamek przeniesienie p ma wartość
			// większą od zera, to jest ono równe pierwszej cyfrze
			if (!j && przeniesienie) dziesietnyUlamek = (char)(przeniesienie + 48) + dziesietnyUlamek;
		};													// Następna cyfra binarna
		licznik1++;
	};
	/*teraz wystarczy podzielić ułamek przez 1/(2^liczba występujących miejsc po przecinku)*/
	char *doKonwersji = new char[dziesietnyUlamek.length() + 1];				
	short int *dzielonyUlamek = new short int[dziesietnyUlamek.length()];
	strcpy(doKonwersji, dziesietnyUlamek.c_str());
	/*cin.ignore();
	for(int i=0; i<dziesietnyUlamek.length()+1; i++)
	{
	cout << doKonwersji[i];
	}
	cin.ignore();*/
	//cin.ignore();
	for (int i = 0; i<dziesietnyUlamek.length(); i++)			//ze stringa robię znów tablicę liczbową
	{
		dzielonyUlamek[i] = doKonwersji[i] - 48;
	}
	/*for(int i=0; i<dziesietnyUlamek.length(); i++)
	{
	cout << dzielonyUlamek[i];
	}
	cout << endl;
	cout << dziesietnyUlamek.length() << endl;
	cin.ignore();
	cout << rozmiarUlamek << endl;*/
	for (int i = 0; i<rozmiarUlamek; i++)				//podziel na dwa, tyle razy jak ile jest cyfr BINARNYCH!!!
	{
		/*if (dzielonyUlamek[0] == 0)
		{
			for (int licznik2 = 0; licznik2<dziesietnyUlamek.length(); licznik2++)
			{
				dzielonyUlamek[licznik2] = dzielonyUlamek[licznik2+1];
			}
			dzielonyUlamek[dziesietnyUlamek.length()-1]=0;
		}*/
		for (int j = 0; j<dziesietnyUlamek.length(); j++)			//jak długi jest ułamek
		{
			if(dzielonyUlamek[j]%2==0)								//jeśli dzielenie nie daje reszty
			{
				dzielonyUlamek[j] = dzielonyUlamek[j] / 2;			//to wpisz po prostu wynik tego dzielenia
				//cout << "if " << j << endl;
			}
			else
			{
				dzielonyUlamek[j] = dzielonyUlamek[j] / 2;			//w przeciwnym wypadnku podziel też na dwa
				dzielonyUlamek[j+1]=dzielonyUlamek[j+1] + 10;		//ale w następnej komórce dodaj 10
				//cout << "else " << j << endl;
			}
			/*if (dzielonyUlamek[j] == 0)							//bez tego ifa działało z dokładnością do 0,01 dla przykładowej liczby
			{													//nie wiem, jak dla innych. A teraz wogóle nie dziala.
				dzielonyUlamek[j] = 0;
			}
			else
			{*/
				//dzielonyUlamek[j + 1] = dzielonyUlamek[j + 1] + 10 * (dzielonyUlamek[j] % 2);
				//dzielonyUlamek[j] = dzielonyUlamek[j] / 2;
			//}
		}
		if (dzielonyUlamek[0] == 0)						//i to zjada wszystkie zera z przodu, a tablicę muszę przesuwać
		{
			for (int licznik2 = 0; licznik2<dziesietnyUlamek.length(); licznik2++)
			{
				dzielonyUlamek[licznik2] = dzielonyUlamek[licznik2+1];
			}
			dzielonyUlamek[dziesietnyUlamek.length()-1]=0;
		}
		/*for (int j = 0; j<dziesietnyUlamek.length(); j++)
		{
			cout << dzielonyUlamek[j];
		}
			cout << endl;*/
		/*if (dzielonyUlamek[0] == 0)
		{
			for (int licznik2 = 0; licznik2<dziesietnyUlamek.length(); licznik2++)
			{
				dzielonyUlamek[licznik2] = dzielonyUlamek[licznik2 + 1];
			}
		}*/
	}
	//cout << dziesietnyUlamek.length() << endl;
	//cout << dziesietnyUlamek << endl;
	/*for(int i=0; i<dziesietnyUlamek.length(); i++)
	{
	cout << dzielonyUlamek[i];
	}
	cout << endl;
	cin.ignore();*/
	//cout << iloscZer << endl;
	/*int zeraUlamekBin = 0;
	int zeraUlamekDec = 0;
	for(int i = 0; i<rozmiarUlamek; i++)
	{
		zeraUlamekBin--;
		if (ulamek[i]==1)
			break;
	}
	cout << zeraUlamekBin << endl;
	cout << pow(2.0, zeraUlamekBin) << endl;*/
	//delete ulamek;
	//------------------------Wyświetlanie-------------------------

	cout << "I z powrotem na dziesiętny:\n" << z << dziesietnaCalosc << ".";
	for(int i=0; i<zero; i++)
		cout << "0";
	for(int i=0; i<dziesietnyUlamek.length(); i++)
	{
	cout << dzielonyUlamek[i];
	}
	cout << endl;
}
int128 int128::Mnozenie(int128 a, int128 b)
{
	int128 wynik;
	wynik.znak=0;
	for(int i=0; i<15; i++)							//zerowanie zmiennej wynik
	{
		wynik.wykladnik[i]=0;
	}
	for(int i=0; i<4080; i++)
	{
		wynik.mantysa[i]=0;
	}
	a.calosc[0]=1;									//uzupełnianie "ukrytej jedynki"
	b.calosc[0]=1;
	for(int i=1; i<4081; i++)
	{
		a.calosc[i]=a.mantysa[i-1];
	}
	for(int i=1; i<4081; i++)
	{
		b.calosc[i]=b.mantysa[i-1];
	}
	//--------------------------------Znak-------------------------------------
	if (a.znak == 1 && b.znak == 1)
	{
		wynik.znak = 0;							//minus razy minus daje plus
	}
	else if (a.znak == 0 && b.znak == 1)
	{
		wynik.znak = 1;							//plus razy minus daje minus
	}
	else if (a.znak == 1 && b.znak == 0)
	{
		wynik.znak = 1;							//minus razy plus daje minus
	}
	else
	{
		wynik.znak = 0;							//plus razy plus daje plus
	}
	//------------------------------Wykladnik----------------------------------
	int wyklA, wyklB =0;						//trzymają dziesiętne wartości wykładników
	int wykl = 0;
	int c = 0;
	for (int i = 14; i >= 0; i--)				//konwersja wykładników, by
	{
		if (a.wykladnik[i] == 1)				//gdy jest jedynka na danej pozycji
		{
			wykl = wykl + pow(2.0, c);			//dodawanie do zmiennej potęgi dwójki na pozycji, na której pojawiła się jedynka
		}
		c++;
	}
	//cout << wykl << endl;
	wykl = wykl - 16383;						//zdjąć obiciążenie
	wyklA = wykl;
	/*cout << endl;
	cout << wykl << endl;
	cout << endl;//*/							//i tu się pojawia problem - zmieniam na nautralny binarny liczbę ujemną...
	bool minusA, minusB = false;						//dlatego tworzę nową zmienną, która będzie mnie informowała, czy wykładnik był ujemny, czy nie
	if (wykl>0)
	{
		for (int i = 14; i>=0; i--)					//zmiana na naturalny binarny - czysta wartość wykładnika
		{
			a.wykladnik[i]=wykl%2;					//reszta z dzielenia dziesiętnego odpowiednika przez dwa i zapis na konkretnej pozycji
			wykl=wykl/2;							//dzielenie dziesiętnego odpowiednika na dwa
		}
	}
	else
	{
		wykl=abs(wykl);								//biorę wartość bezwzględną
		minusA = true;								//zmieniam stan minusa
		for (int i = 14; i>=0; i--)					//zmiana na naturalny binarny - czysta wartość wykładnika
		{
			a.wykladnik[i]=wykl%2;					//reszta z dzielenia dziesiętnego odpowiednika przez dwa i zapis na konkretnej pozycji
			wykl=wykl/2;							//dzielenie dziesiętnego odpowiednika na dwa
		}
	}
	/*for (int i =0; i<15; i++)
	{
		cout << a.wykladnik[i];
	}
	cout << endl;
	cin.ignore();//*/
	wykl = 0;
	c = 0;
	for (int i = 14; i >= 0; i--)					//tak samo jak z wykładnikiem pierwszej liczby
	{
		if (b.wykladnik[i] == 1)
		{
			wykl = wykl + pow(2.0, c);
		}
		c++;
	}
	//cout << wykl << endl;
	wykl = wykl - 16383;
	wyklB=wykl;
	/*cout << endl;
	cout << wykl << endl << endl;//*/
	if (wykl > 0)
	{
		for (int i = 14; i>=0; i--)
		{
			b.wykladnik[i]=wykl%2;
			wykl=wykl/2;
		}
	}
	else
	{
		wykl=abs(wykl);
		minusB=true;
		for (int i = 14; i>=0; i--)
		{
			b.wykladnik[i]=wykl%2;
			wykl=wykl/2;
		}
	}
	/*for (int i =0; i<15; i++)
	{
		cout << b.wykladnik[i];
	}
	cout << endl;
	cin.ignore();//*/
	int pozyczka = 0;								//miejsce, gdzie jest potrzebana pozyczka
	int miejsce = 0;								//miejsce, z którego pozyczka została wizięta
	bool minusW=false;											//czy w przypadku gdy wyjdzie wykładnik ujemny muszę to potem uwzględnić
	if((abs(wyklA)>=abs(wyklB))&&(minusA==false && minusB==true))			//+wykładnik wyniku, będzie odejmowanie, a większe
	{
		for (int i = 14; i >= 0; i--)				//odejmowanie wykładników
		{
			if(a.wykladnik[i]==1 && b.wykladnik[i]==1)	
				a.wykladnik[i]=0;						//gdy 1-1 wpisz 0 do a.wykladnik, w którym na razie trzymany jest wynik
			else if(a.wykladnik[i]==1 && b.wykladnik[i]==0)
				a.wykladnik[i]=1;						//gdy 1-0 wpisz 1 do a.wykladnik
			else if(a.wykladnik[i]==0 && b.wykladnik[i]==0)
				a.wykladnik[i]=0;						//gdy 0-0 wpisz 0 do a.wykladnik
			else
			{										//gdy 0-1 potrzebna jest pożyczka
				pozyczka = i;						//zaznaczam miejsce, którym jest potrzebna
				for(int j=pozyczka; j>=0; j--)		//od miejsca pierwszej pożyczki, do końca
				{
					if(a.wykladnik[j]==1)				//szukaj 1, czyli miejsca z którego można wziąć pożyczkę
					{
						miejsce=j;
						a.wykladnik[j]=0;				//wypełnij to miejsce 0
						break;						//wyjdź z pętli
					}
				}
				for(int j=pozyczka; j>miejsce; j--)	//od miejsca, gdzie pożyczka była potrzebna
				{									//do miejsca, z którego pożyczka została wzięta, wypełnij wszystko jedynkami
						a.wykladnik[j]=1;
				}
				a.wykladnik[pozyczka]=1;				//tam, gdzie pożyczka była potrzena wstaw 1, bo 2-1=1
			}
		}
		for (int i=0; i<15; i++)									//zapisanie wykładnika wyniku
		{
			wynik.wykladnik[i]=a.wykladnik[i];
		}
	}
	else if((abs(wyklA)<abs(wyklB))&&(minusA==true && minusB==false))			//+wykładnik wyniku, będzie odejmowanie, tylko b jest większe
	{
		for (int i = 14; i >= 0; i--)				//odejmowanie wykładników
		{
			if(b.wykladnik[i]==1 && a.wykladnik[i]==1)	
				b.wykladnik[i]=0;						//gdy 1-1 wpisz 0 do b.wykladnik, w którym na razie trzymany jest wynik
			else if(b.wykladnik[i]==1 && a.wykladnik[i]==0)
				b.wykladnik[i]=1;						//gdy 1-0 wpisz 1 do b.wykladnik
			else if(a.wykladnik[i]==0 && a.wykladnik[i]==0)
				b.wykladnik[i]=0;						//gdy 0-0 wpisz 0 do b.wykladnik
			else
			{										//gdy 0-1 potrzebna jest pożyczka
				pozyczka = i;						//zaznaczam miejsce, którym jest potrzebna
				for(int j=pozyczka; j>=0; j--)		//od miejsca pierwszej pożyczki, do końca
				{
					if(b.wykladnik[j]==1)				//szukaj 1, czyli miejsca z którego można wziąć pożyczkę
					{
						miejsce=j;
						b.wykladnik[j]=0;				//wypełnij to miejsce 0
						break;						//wyjdź z pętli
					}
				}
				for(int j=pozyczka; j>miejsce; j--)	//od miejsca, gdzie pożyczka była potrzebna
				{									//do miejsca, z którego pożyczka została wzięta, wypełnij wszystko jedynkami
						b.wykladnik[j]=1;
				}
				b.wykladnik[pozyczka]=1;				//tam, gdzie pożyczka była potrzena wstaw 1, bo 2-1=1
			}
		}
		for (int i=0; i<15; i++)									//zapisanie wykładnika wyniku
		{
			wynik.wykladnik[i]=b.wykladnik[i];
		}
	}
	else if((abs(wyklA)>=abs(wyklB))&&(minusA==true && minusB==false))			//-wykładnik wyniku, będzie odejmowanie
	{
		minusW=true;
		for (int i = 14; i >= 0; i--)				//odejmowanie wykładników
		{
			if(a.wykladnik[i]==1 && b.wykladnik[i]==1)	
				a.wykladnik[i]=0;						//gdy 1-1 wpisz 0 do a.wykladnik, w którym na razie trzymany jest wynik
			else if(a.wykladnik[i]==1 && b.wykladnik[i]==0)
				a.wykladnik[i]=1;						//gdy 1-0 wpisz 1 do a.wykladnik
			else if(a.wykladnik[i]==0 && b.wykladnik[i]==0)
				a.wykladnik[i]=0;						//gdy 0-0 wpisz 0 do a.wykladnik
			else
			{										//gdy 0-1 potrzebna jest pożyczka
				pozyczka = i;						//zaznaczam miejsce, którym jest potrzebna
				for(int j=pozyczka; j>=0; j--)		//od miejsca pierwszej pożyczki, do końca
				{
					if(a.wykladnik[j]==1)				//szukaj 1, czyli miejsca z którego można wziąć pożyczkę
					{
						miejsce=j;
						a.wykladnik[j]=0;				//wypełnij to miejsce 0
						break;						//wyjdź z pętli
					}
				}
				for(int j=pozyczka; j>miejsce; j--)	//od miejsca, gdzie pożyczka była potrzebna
				{									//do miejsca, z którego pożyczka została wzięta, wypełnij wszystko jedynkami
						a.wykladnik[j]=1;
				}
				a.wykladnik[pozyczka]=1;				//tam, gdzie pożyczka była potrzena wstaw 1, bo 2-1=1
			}
		}
		for (int i=0; i<15; i++)									//zapisanie wykładnika wyniku
		{
			wynik.wykladnik[i]=a.wykladnik[i];
		}
	}
	else if ((abs(wyklA)<abs(wyklB))&&(minusA==false && minusB==true))			//-wykładnik wyniku, będzie odejmowanie
	{
		minusW=true;
		for (int i = 14; i >= 0; i--)				//odejmowanie wykładników
		{
			if(b.wykladnik[i]==1 && a.wykladnik[i]==1)	
				b.wykladnik[i]=0;						//gdy 1-1 wpisz 0 do b.wykladnik, w którym na razie trzymany jest wynik
			else if(b.wykladnik[i]==1 && a.wykladnik[i]==0)
				b.wykladnik[i]=1;						//gdy 1-0 wpisz 1 do b.wykladnik
			else if(b.wykladnik[i]==0 && a.wykladnik[i]==0)
				b.wykladnik[i]=0;						//gdy 0-0 wpisz 0 do b.wykladnik
			else
			{										//gdy 0-1 potrzebna jest pożyczka
				pozyczka = i;						//zaznaczam miejsce, którym jest potrzebna
				for(int j=pozyczka; j>=0; j--)		//od miejsca pierwszej pożyczki, do końca
				{
					if(b.wykladnik[j]==1)				//szukaj 1, czyli miejsca z którego można wziąć pożyczkę
					{
						miejsce=j;
						b.wykladnik[j]=0;				//wypełnij to miejsce 0
						break;						//wyjdź z pętli
					}
				}
				for(int j=pozyczka; j>miejsce; j--)	//od miejsca, gdzie pożyczka była potrzebna
				{									//do miejsca, z którego pożyczka została wzięta, wypełnij wszystko jedynkami
						b.wykladnik[j]=1;
				}
				b.wykladnik[pozyczka]=1;				//tam, gdzie pożyczka była potrzena wstaw 1, bo 2-1=1
			}
		}
		for (int i=0; i<15; i++)									//zapisanie wykładnika wyniku
		{
			wynik.wykladnik[i]=b.wykladnik[i];
		}
	}
	else if(((abs(wyklA)>=abs(wyklB))&&(minusA==true && minusB==true)) || ((abs(wyklA)<abs(wyklB))&&(minusA==true && minusB==true)))
	{			//-wykładnik wyniku, będzie dodawanie, wszystko jedno, która pierwsza, bo tu i tu będzie dodawanie
		minusW=true;
		for(int i=14; i>=0; i--)								//dodawanie wykładników i zapisywanie wyniku w wykładniku liczby a
		{														
			if (a.wykladnik[i] == 2)							//dodawanie standardowym systemem w tym programie
			{
				a.wykladnik[i] = 0;								
				a.wykladnik[i - 1]++;
			}
			if (a.wykladnik[i] == 0 && b.wykladnik[i] == 0)
			{
				a.wykladnik[i] = 0;
			}
			else if (a.wykladnik[i] == 0 && b.wykladnik[i] == 1)
			{
				a.wykladnik[i] = 1;
			}
			else if (a.wykladnik[i] == 1 && b.wykladnik[i] == 0)
			{
				a.wykladnik[i] = 1;
			}
			else if (a.wykladnik[i] == 1 && b.wykladnik[i] == 1)
			{
				a.wykladnik[i] = 0;
				a.wykladnik[i - 1]++;
			}
		}
		for (int i=0; i<15; i++)									//zapisanie wykładnika wyniku
		{
			wynik.wykladnik[i]=a.wykladnik[i];
		}
	}
	else
	{
		for(int i=14; i>=0; i--)								//dodawanie wykładników i zapisywanie wyniku w wykładniku liczby a
		{														
			if (a.wykladnik[i] == 2)							//dodawanie standardowym systemem w tym programie
			{
				a.wykladnik[i] = 0;								
				a.wykladnik[i - 1]++;
			}
			if (a.wykladnik[i] == 0 && b.wykladnik[i] == 0)
			{
				a.wykladnik[i] = 0;
			}
			else if (a.wykladnik[i] == 0 && b.wykladnik[i] == 1)
			{
				a.wykladnik[i] = 1;
			}
			else if (a.wykladnik[i] == 1 && b.wykladnik[i] == 0)
			{
				a.wykladnik[i] = 1;
			}
			else if (a.wykladnik[i] == 1 && b.wykladnik[i] == 1)
			{
				a.wykladnik[i] = 0;
				a.wykladnik[i - 1]++;
			}
		}
		for (int i=0; i<15; i++)									//zapisanie wykładnika wyniku
		{
			wynik.wykladnik[i]=a.wykladnik[i];
		}
	}
	//cout << endl;*/
	//-----------------------------------Mantysa-----------------------------------
	short int wynikMantysy[8163];
	for(int i=0; i<8163; i++)						//na wszelki wypadek zapełnienie wyniku zerami
	{
		wynikMantysy[i]=0;
	}
	int wM = 8163;									//wynik po pomnożeniu mantys będzie dwa razy większy od standardowej mantysy
	int przeniesienie=0;
	int licznik=0;
	for (int i=4080; i>=-1; i--)						//mnożenie mantys
	{
		wM=8163-licznik;								//bez zabawy w sumy częściowe, wynik od razu jest dodawany do tablicy wynikowej, która jest przesuwana o jedną pozycję
		for (int j=4080; j>=-1; j--)					//tu możesz narysować takie ładnie schodki, jak się przesuwają sumy częściowe
		{
			if(a.calosc[j]==0 && b.calosc[i]==0)		//mnoże 0 przez 0
			{
				if (wynikMantysy[wM]==0)				//jeśli w wyniku mam 0
				{
					if (przeniesienie == 1)				//sprawdzam przeniesienie
					{
						wynikMantysy[wM]=1;				//jeśli było, to wpisuję do wyniku 1
						przeniesienie--;				//i zeruję przeniesienie
					}
					else
						wynikMantysy[wM]=0;				//jeśli nie było wpisuję do wyniku 0
				}
				else if(wynikMantysy[wM]==1)			//jeśli w wyniku było 1
				{
					if (przeniesienie == 1)				//a mam przeniesienie
					{
						wynikMantysy[wM]=0;				//znaczy, że mam do wyniku wpisać 0, ale przeniesienie zostaje na jeszcze wyższą pozycję
					}
					else
						wynikMantysy[wM]=1;				//jeśli nie było przeniesienia zostaje 1
				}
			}
			else if(a.calosc[j]==0 && b.calosc[i]==1)	//mnożę 0 przez 1, daje mi zero, dlatego kroki są takie same jak wcześniej
			{
				if (wynikMantysy[wM]==0)
				{
					if (przeniesienie == 1)
					{
						wynikMantysy[wM]=1;
						przeniesienie--;
					}
					else
						wynikMantysy[wM]=0;
				}
				else if(wynikMantysy[wM]==1)
				{
					if (przeniesienie == 1)
					{
						wynikMantysy[wM]=0;
					}
					else
						wynikMantysy[wM]=1;
				}
			}
			else if(a.calosc[j]==1 && b.calosc[i]==0)		//jak wyżej
			{
				if (wynikMantysy[wM]==0)
				{
					if (przeniesienie == 1)
					{
						wynikMantysy[wM]=1;
						przeniesienie--;
					}
					else
						wynikMantysy[wM]=0;
				}
				else if(wynikMantysy[wM]==1)
				{
					if (przeniesienie == 1)
					{
						wynikMantysy[wM]=0;
					}
					else
						wynikMantysy[wM]=1;
				}
			}
			else if(a.calosc[j]==1 && b.calosc[i]==1)			//tu otrzymuję 1
			{
				if (wynikMantysy[wM]==0)						//jeśli w wyniku było 0
				{
					if (przeniesienie == 1)						//a przeniesienie jest równe 1
					{
						wynikMantysy[wM]=0;						//to do wyniku wpisz 0, a przeniesienie zostaje na jeszcze wyższą pozycję
					}
					else
						wynikMantysy[wM]=1;						//jak nie było przeniesienia, wpisz 1
				}
				else if(wynikMantysy[wM]==1)					//jeśli w wyniku było 1
				{
					if (przeniesienie == 1)						//i przeniesienie jest równe 1
					{
						wynikMantysy[wM]=1;						//to wpisz 1 do wyniku, bo jest 1+1+1
						przeniesienie++;						//a przeniesienie będzie musiało zostać uwzględnione na następnej pozycji
					}
					else
					{
						wynikMantysy[wM]=0;						//jeśli nie ma przeniesienia, to mam 1+1, czyli wpisuję zero
						przeniesienie++;						//a przeniesienie zostaje
					}
				}
			}
			wM--;												//i działam na kolejnej pozycji
		}
		licznik++;												//zwiększam licznik, tak, by następną pętlę zacząć o schodek bardziej w lewo
	}
	//-----------------------------------------------Normowanie wyniku--------------------------------
	int ileWykladnik = 0;										//ile wykładnik ma zostać zmieniony i czy wogóle
	for (int i=0; i<8163; i++)									//sprawdzam, gdzie występuje pierwsza jedynka wyniku
	{
		if (wynikMantysy[i]==1)
		{
			ileWykladnik=i;
			break;												//gdy znajdę, wychodzę z pętli
		}
	}
	//cout << ileWykladnik << endl;
	/*for (int i = 0; i<8163; i++)
	{
		cout << wynikMantysy[i];
	}
	cout << endl;//*/
	licznik=0;								//wpisuję tak mantysę, by pominąć pierwszą jedynkę i wpisać wszystko inne
	for (int i=ileWykladnik+1; i<ileWykladnik+4080; i++)
	{
		//cout << wynikMantysy[i];
		wynik.mantysa[licznik]=wynikMantysy[i];
		licznik++;
	}
	//cout << endl << endl;
	wykl = 0;								//liczenie wykładnika
	c = 0;
	for (int i = 14; i >= 0; i--)			//z naturalnego binarnego zamieniam na dziesiętny
	{
		if (wynik.wykladnik[i] == 1)
		{
			wykl = wykl + pow(2.0, c);		//dodając do siebie kolejne potęgi dwójki na odpowiednich pozycjach
		}
		c++;
	}
	if(minusW==true)						//tam, gdzie ustaliłam, że będzie ujemny wynik zaznaczam to teraz, przed nałożeniem obciążenia
	{
		wykl=0-wykl;
	}
	//cout << wykl << endl << endl;			//nakładanie obiciążenia
	wykl = wykl + 16383;
	if (ileWykladnik>3)						//do wykładnika muszę jeszcze coś dodać, jeśli wynik się przesunął
		wykl = wykl - ileWykladnik-3;
	else if (ileWykladnik==2)
		wykl = wykl + 1;
	else if (ileWykladnik==1)
		wykl = wykl + 2;//*/
	//cout << wykl << endl;
	for (int i = 14; i>=0; i--)				//zamieniam na binarny z obciążeniem
	{
		wynik.wykladnik[i]=wykl%2;
		wykl=wykl/2;
	}
	wynik.zero=a.zero+b.zero;				//może uda się to rozwiązać w inny sposób
	/*for (int i =0; i<15; i++)
	{
		cout << wynik.wykladnik[i];
	}
	cout << endl;
	cin.ignore();//*/
	//---------------------------------------------Wyswietlanie wyniku-----------------------------
	cout << wynik.znak << " ";
	for (int i = 0; i < 15; i++)
	{
		cout << wynik.wykladnik[i];
	}
	cout << " ";
	for (int i = 0; i<4080; i++)
	{
		cout << wynik.mantysa[i];
	}
	cout << endl;
	return wynik;
}
int128 int128::Odejmowanie(int128 a, int128 b)
{
	int128 wynik;
	//---------------------------------Na podstawie tego zrobiłam odejmowanie i pożyczki-----------------------------
	int pozyczka = 0;								//miejsce, gdzie jest potrzebana pozyczka
	int miejsce = 0;								//miejsce, z którego pozyczka została wizięta
	/*for(int i=pozyczka; i>=0; i--)
	{
		if(a.calosc[i]==1)
		{
			miejsce=i;
			a.calosc[i]=0;
			break;
		}
	}
	for(int i=miejsce; i>pozyczka; i--)
	{
			a.calosc[i]=1;
	}
	a.calosc[pozyczka]=2;//*/

	wynik.znak=0;											//zerowanie wszystkiego
	for(int i=0; i<15; i++)
	{
		wynik.wykladnik[i]=0;
	}
	for(int i=0; i<4080; i++)
	{
		wynik.mantysa[i]=0;
	}
	int wykla = 0;
	int wyklb = 0;
	int c = 0;
	for (int i = 14; i >= 0; i--)								//zmiana wykładników na dziesiętny, żeby sprawdzić, która liczba jest większa
	{
		if (a.wykladnik[i] == 1)
		{
			wykla = wykla + pow(2.0, c);
		}
		c++;
	}
	wykla = wykla- 16383;										//odejmowanie obicążenia
	c = 0;
	for (int i = 14; i >= 0; i--)
	{
		if (b.wykladnik[i] == 1)
		{
			wyklb = wyklb + pow(2.0, c);
		}
		c++;
	}
	//cout << wykl << endl;
	wyklb = wyklb - 16383;
	/*cout << endl;
	cout << wykl << endl << endl;//*/
	a.calosc[0]=1;											//dopisywanie ukrytej jedynki
	b.calosc[0]=1;
	for(int i=1; i<4081; i++)								//wypełnianie reszty mantysą
	{
		a.calosc[i]=a.mantysa[i-1];
	}
	for(int i=1; i<4081; i++)
	{
		b.calosc[i]=b.mantysa[i-1];
	}
	if	(wykla>wyklb)										//ten wykładnik, który większy będzie główny
	{
		//--------------------------------Znak-----------------------------------
		if (a.znak == 1 && b.znak == 1)
		{
			wynik.znak = 1;									//-15-(-10)=-15+10=-5
		}
		else if (a.znak == 0 && b.znak == 1)
		{
			wynik.znak = 0;									//dodawanie! 15-(-10)=15+10=25
		}
		else if (a.znak == 1 && b.znak == 0)
		{
			wynik.znak = 1;									//dodawanie! -15-10=-25
		}
		else
		{
			wynik.znak = 0;									//15-10=5
		}
		//----------------------------------Wykladnik----------------------------
		int ileZer = 0;								//sprawdzanie jak dużo większa jest jedna liczba od drugiej
		while (wykla>wyklb)							//jeśli dobrze myślę, to potem tyle razy będzie trzeba odjąć 1 od wykładnika
		{											//nope, druga linijka komentarza to kompletnie bzdury
			ileZer++;								//im więcej będzie zer, tym mniejsza szansa na zmianę wykładnika
			wyklb++;								//przeliczanie wykładnika będzie trzeba się zająć później -> ile zer z przodu tyle będzie trzeba odjąć od wykładnika
		}
		for(int i = 0; i<15; i++)					//póki co przypisuję wykładnikowi wyniku wykładnik liczby większej, później się go unormuje
		{
			wynik.wykladnik[i]=a.wykladnik[i];
		}
		
		//---------------------------------Mantysa-------------------------------
		short int tym[4081];						//Potrzebuję tego, bo wcześniej "Zmieniałam na to co już zostało zmienione"
		for (int i = 0; i<4081; i++)
			tym[i] = b.calosc[i];
		for (int i = 0; i<ileZer; i++)				//dopisywanie zer z przodu, żeby mantysa odpowiadała zwiększonemu wykłdanikowi
			b.calosc[i] = 0;
		for (int i = ileZer; i<4081; i++)			//spisywanie mantysy z ukrytą jedynką od miejsca, w którym kończą się zera
			b.calosc[i] = tym[i-ileZer];
		for (int i = 4080; i >= 0; i--)				//odejmowanie mantys
		{
			if(a.calosc[i]==1 && b.calosc[i]==1)	
				a.calosc[i]=0;						//gdy 1-1 wpisz 0 do a.calosc, w którym na razie trzymany jest wynik
			else if(a.calosc[i]==1 && b.calosc[i]==0)
				a.calosc[i]=1;						//gdy 1-0 wpisz 1 do a.calosc
			else if(a.calosc[i]==0 && b.calosc[i]==0)
				a.calosc[i]=0;						//gdy 0-0 wpisz 0 do a.calosc
			else
			{										//gdy 0-1 potrzebna jest pożyczka
				pozyczka = i;						//zaznaczam miejsce, którym jest potrzebna
				for(int j=pozyczka; j>=0; j--)		//od miejsca pierwszej pożyczki, do końca
				{
					if(a.calosc[j]==1)				//szukaj 1, czyli miejsca z którego można wziąć pożyczkę
					{
						miejsce=j;
						a.calosc[j]=0;				//wypełnij to miejsce 0
						break;						//wyjdź z pętli
					}
				}
				for(int j=pozyczka; j>miejsce; j--)	//od miejsca, gdzie pożyczka była potrzebna
				{									//do miejsca, z którego pożyczka została wzięta, wypełnij wszystko jedynkami
						a.calosc[j]=1;
				}
				a.calosc[pozyczka]=1;				//tam, gdzie pożyczka była potrzena wstaw 1, bo 2-1=1
			}
		}
		/*for (int i = 0; i<4081; i++)
				cout << wynikCalosc[i];
			cout << endl << endl;//*/
		int ilosc = 0;
		for(int i=0; i<4081; i++)					//ile zer, o tyle trzeba przesunąć mantysę tak do jedynki
		{											//oraz zmiejszyć wykadnik o jeden tyle razy, żeby pasowała do stanu mantysy
			if(a.calosc[i]==0)
			{
				ilosc++;
			}
			else
			{
				break;
			}
		}
		if (a.calosc[0]==0)							//normowanie wyniku, jeśli na pozycji, gdzie w pierwszej liczbie była jedynka,
		{											//a teraz jej nie ma trzeba zmniejszyć wykładnik
			for(int j=0; j<ilosc; j++)				//i to o tyle razy ile jest pozycji z zerami z przodu
			{
				if(wynik.wykladnik[14]==0)			//jeśli ostatnia pozycja jest równa 0, to potrzebna jest pożyczka na tym właśnie miejscu
				{
					pozyczka = 14;					//czyli jak wcześniej - miejsce pożyczki jest ustalone
					for(int i=pozyczka; i>=0; i--)	//teraz trzeba znaleźć jedynkę, którą można zarekwirować
					{
						if(wynik.wykladnik[i]==1)
						{
							miejsce=i;
							wynik.wykladnik[i]=0;
							break;
						}
					}
					for(int i=pozyczka; i>miejsce; i--)
					{
						wynik.wykladnik[i]=1;
					}
					wynik.wykladnik[pozyczka]=1;
				}
				else								//jeśli na ostatnim miejscu jest 1, to ją zamień na zero
				{
					wynik.wykladnik[14]=0;
				}
			}
			for(int i = 0; i < 4080; i++)			//wypełnij mantysę wyniku od miejsca po pierwszej jedynki do końca
			{
				wynik.mantysa[i]=a.calosc[i+ilosc+1];
			}
			for(int i=4080-ilosc+1; i<4080; i++)	//resztę wypełnij zerami
			{
				wynik.mantysa[i]=0;
			}
		}
		else										//jeśli na pierwszym miejscu jednyka się "uchowała" 
		{											//to ją pomiń i spisz mantysę do wyniku
			for(int i = 0; i < 4080; i++)
			{
				wynik.mantysa[i]=a.calosc[i+1];
			}
		}
		//----------------------------------Wyświetlanie-------------------------
		cout << wynik.znak << " ";					//wszystko jasne
		for (int i = 0; i < 15; i++)
			cout << wynik.wykladnik[i];
		cout << " ";
		for (int i = 0; i < 4080; i++)
			cout << wynik.mantysa[i];
		cout << endl;
	}
	else if(wyklb>wykla)							//analogicznie, teraz druga liczba jest większa -- ZMIENIĄ SIĘ ZNAKI!
	{
		//--------------------------------Znak-----------------------------------
		if (a.znak == 1 && b.znak == 1)
		{
			wynik.znak = 0;									//-10-(-15)=-10+15=5
		}
		else if (a.znak == 0 && b.znak == 1)
		{
			wynik.znak = 0;									//dodawanie! 10-(-15)=10+15=25
		}
		else if (a.znak == 1 && b.znak == 0)
		{
			wynik.znak = 1;									//dodawanie! -10-15=-25
		}
		else
		{
			wynik.znak = 1;									//10-15=-5
		}
		//----------------------------------Wykladnik----------------------------
		int ileZer = 0;								//sprawdzanie jak dużo większa jest jedna liczba od drugiej
		while (wyklb>wykla)							//jeśli dobrze myślę, to potem tyle razy będzie trzeba odjąć 1 od wykładnika
		{											//nope, druga linijka komentarza to kompletnie bzdury
			ileZer++;								//im więcej będzie zer, tym mniejsza szansa na zmianę wykładnika
			wykla++;								//przeliczanie wykładnika będzie trzeba się zająć później -> ile zer z przodu tyle będzie trzeba odjąć od wykładnika
		}
		for(int i = 0; i<15; i++)					//póki co przypisuję wykładnikowi wyniku wykładnik liczby większej, później się go unormuje
		{
			wynik.wykladnik[i]=b.wykladnik[i];
		}
		
		//---------------------------------Mantysa-------------------------------
		short int tym[4081];						//Potrzebuję tego, bo wcześniej "Zmieniałam na to co już zostało zmienione"
		for (int i = 0; i<4081; i++)
			tym[i] = a.calosc[i];
		for (int i = 0; i<ileZer; i++)				//dopisywanie zer z przodu, żeby mantysa odpowiadała zwiększonemu wykłdanikowi
			a.calosc[i] = 0;
		for (int i = ileZer; i<4081; i++)			//spisywanie mantysy z ukrytą jedynką od miejsca, w którym kończą się zera
			a.calosc[i] = tym[i-ileZer];
		for (int i = 4080; i >= 0; i--)				//odejmowanie mantys
		{
			if(b.calosc[i]==1 && a.calosc[i]==1)	
				b.calosc[i]=0;						//gdy 1-1 wpisz 0 do a.calosc, w którym na razie trzymany jest wynik
			else if(b.calosc[i]==1 && a.calosc[i]==0)
				b.calosc[i]=1;						//gdy 1-0 wpisz 1 do a.calosc
			else if(b.calosc[i]==0 && a.calosc[i]==0)
				b.calosc[i]=0;						//gdy 0-0 wpisz 0 do a.calosc
			else
			{										//gdy 0-1 potrzebna jest pożyczka
				pozyczka = i;						//zaznaczam miejsce, którym jest potrzebna
				for(int j=pozyczka; j>=0; j--)		//od miejsca pierwszej pożyczki, do końca
				{
					if(b.calosc[j]==1)				//szukaj 1, czyli miejsca z którego można wziąć pożyczkę
					{
						miejsce=j;
						b.calosc[j]=0;				//wypełnij to miejsce 0
						break;						//wyjdź z pętli
					}
				}
				for(int j=pozyczka; j>miejsce; j--)	//od miejsca, gdzie pożyczka była potrzebna
				{									//do miejsca, z którego pożyczka została wzięta, wypełnij wszystko jedynkami
						b.calosc[j]=1;
				}
				b.calosc[pozyczka]=1;				//tam, gdzie pożyczka była potrzena wstaw 1, bo 2-1=1
			}
		}
		/*for (int i = 0; i<4081; i++)
				cout << wynikCalosc[i];
			cout << endl << endl;//*/
		int ilosc;
		for(int i=0; i<4081; i++)					//ile zer, o tyle trzeba przesunąć mantysę tak do jedynki
		{											//oraz zmiejszyć wykadnik o jeden tyle razy, żeby pasowała do stanu mantysy
			if(b.calosc[i]==0)
			{
				ilosc++;
			}
			else
			{
				break;
			}
		}
		if (b.calosc[0]==0)							//normowanie wyniku, jeśli na pozycji, gdzie w pierwszej liczbie była jedynka,
		{											//a teraz jej nie ma trzeba zmniejszyć wykładnik
			for(int j=0; j<ilosc; j++)				//i to o tyle razy ile jest pozycji z zerami z przodu
			{
				if(wynik.wykladnik[14]==0)			//jeśli ostatnia pozycja jest równa 0, to potrzebna jest pożyczka na tym właśnie miejscu
				{
					pozyczka = 14;					//czyli jak wcześniej - miejsce pożyczki jest ustalone
					for(int i=pozyczka; i>=0; i--)	//teraz trzeba znaleźć jedynkę, którą można zarekwirować
					{
						if(wynik.wykladnik[i]==1)
						{
							miejsce=i;
							wynik.wykladnik[i]=0;
							break;
						}
					}
					for(int i=pozyczka; i>miejsce; i--)
					{
						wynik.wykladnik[i]=1;
					}
					wynik.wykladnik[pozyczka]=1;
				}
				else								//jeśli na ostatnim miejscu jest 1, to ją zamień na zero
				{
					wynik.wykladnik[14]=0;
				}
			}
			for(int i = 0; i < 4080; i++)			//wypełnij mantysę wyniku od miejsca po pierwszej jedynki do końca
			{
				wynik.mantysa[i]=b.calosc[i+ilosc+1];
			}
			for(int i=4080-ilosc+1; i<4080; i++)	//resztę wypełnij zerami
			{
				wynik.mantysa[i]=0;
			}
		}
		else										//jeśli na pierwszym miejscu jednyka się "uchowała" 
		{											//to ją pomiń i spisz mantysę do wyniku
			for(int i = 0; i < 4080; i++)
			{
				wynik.mantysa[i]=b.calosc[i+1];
			}
		}
		//----------------------------------Wyświetlanie-------------------------
		cout << wynik.znak << " ";					//wszystko jasne
		for (int i = 0; i < 15; i++)
			cout << wynik.wykladnik[i];
		cout << " ";
		for (int i = 0; i < 4080; i++)
			cout << wynik.mantysa[i];
		cout << endl;
	}
	else											//ale co w przypadku, gdy wykładniki są równe? trzeba sprawdzić mantysy
	{												//konwersja, czy lepszy sposób? lepszy!
		int iloscA, iloscB = 0;						//sprawdzając gdzie występuje pierwsza jedynka w manysie jednej i drugiej liczby
		for(int i=0; i<4080; i++)					//dowiem się, która z nich jest większa
		{
			if(a.mantysa[i]==0)
				iloscA++;
			else
				break;
		}
		for(int i=0; i<4080; i++)
		{
			if(b.mantysa[i]==0)
				iloscB++;
			else
				break;
		}
		for(int i = 0; i<15; i++)					//póki co przypisuję wykładnikowi wyniku wykładnik liczby większej, później się go unormuje
		{
			wynik.wykladnik[i]=a.wykladnik[i];
		}
		if(iloscA>iloscB)
		{
			//--------------------------------Znak-----------------------------------
			if (a.znak == 1 && b.znak == 1)
			{
				wynik.znak = 1;									//-15-(-10)=-15+10=-5
			}
			else if (a.znak == 0 && b.znak == 1)
			{
				wynik.znak = 0;									//dodawanie! 15-(-10)=15+10=25
			}
			else if (a.znak == 1 && b.znak == 0)
			{
				wynik.znak = 1;									//dodawanie! -15-10=-25
			}
			else
			{
				wynik.znak = 0;									//15-10=5
			}
			//--------------------------Mantysa--------------------------------------
			for (int i = 4080; i >= 0; i--)				//odejmowanie mantys
			{
				if(a.calosc[i]==1 && b.calosc[i]==1)	
					a.calosc[i]=0;						//gdy 1-1 wpisz 0 do a.calosc, w którym na razie trzymany jest wynik
				else if(a.calosc[i]==1 && b.calosc[i]==0)
					a.calosc[i]=1;						//gdy 1-0 wpisz 1 do a.calosc
				else if(a.calosc[i]==0 && b.calosc[i]==0)
					a.calosc[i]=0;						//gdy 0-0 wpisz 0 do a.calosc
				else
				{										//gdy 0-1 potrzebna jest pożyczka
					pozyczka = i;						//zaznaczam miejsce, którym jest potrzebna
					for(int j=pozyczka; j>=0; j--)		//od miejsca pierwszej pożyczki, do końca
					{
						if(a.calosc[j]==1)				//szukaj 1, czyli miejsca z którego można wziąć pożyczkę
						{
							miejsce=j;
							a.calosc[j]=0;				//wypełnij to miejsce 0
							break;						//wyjdź z pętli
						}
					}
					for(int j=pozyczka; j>miejsce; j--)	//od miejsca, gdzie pożyczka była potrzebna
					{									//do miejsca, z którego pożyczka została wzięta, wypełnij wszystko jedynkami
							a.calosc[j]=1;
					}
					a.calosc[pozyczka]=1;				//tam, gdzie pożyczka była potrzena wstaw 1, bo 2-1=1
				}
			}
			int ilosc = 0;								
			/*for(int i=0; i<4081; i++)
			{
				cout << a.calosc[i];
			}//*/
			cout << endl;//*/							//bez tego program nie działa. Czemu? Nie wiem...
			for(int i=0; i<4081; i++)					//tak jak wyżej, sprawdzanie gdzie jest pierwsza jedynka 
			{
				if(a.calosc[i]==0)
				{
					ilosc++;
				}
				else
					break;
			}
			for(int i=0; i<4080; i++)					//zapisywanie do mantysy
			{
				wynik.mantysa[i]=a.calosc[i+ilosc+1];
			}
			for(int i=4080-ilosc; i<4080; i++)			//resztę wypełnij zerami
			{
				wynik.mantysa[i]=0;
			}
			if (a.calosc[0]==0)							//normowanie wyniku, jeśli na pozycji, gdzie w pierwszej liczbie była jedynka,
			{											//a teraz jej nie ma trzeba zmniejszyć wykładnik
				for(int j=0; j<ilosc; j++)				//i to o tyle razy ile jest pozycji z zerami z przodu
				{
					if(wynik.wykladnik[14]==0)			//jeśli ostatnia pozycja jest równa 0, to potrzebna jest pożyczka na tym właśnie miejscu
					{
						pozyczka = 14;					//czyli jak wcześniej - miejsce pożyczki jest ustalone
						for(int i=pozyczka; i>=0; i--)	//teraz trzeba znaleźć jedynkę, którą można zarekwirować
						{
							if(wynik.wykladnik[i]==1)
							{
								miejsce=i;
								wynik.wykladnik[i]=0;
								break;
							}
						}
						for(int i=pozyczka; i>miejsce; i--)
						{
							wynik.wykladnik[i]=1;
						}
						wynik.wykladnik[pozyczka]=1;
					}
					else								//jeśli na ostatnim miejscu jest 1, to ją zamień na zero
					{
						wynik.wykladnik[14]=0;
					}
				}
			}
			//----------------------------------Wyświetlanie-------------------------
			cout << wynik.znak << " ";					//wszystko jasne
			for (int i = 0; i < 15; i++)
				cout << wynik.wykladnik[i];
			cout << " ";
			for (int i = 0; i < 4080; i++)
				cout << wynik.mantysa[i];
			cout << endl;
		}
		else											//jak wyżej
		{
			//--------------------------------Znak-----------------------------------
			if (a.znak == 1 && b.znak == 1)
			{
				wynik.znak = 0;									//-10-(-15)=-10+15=5
			}
			else if (a.znak == 0 && b.znak == 1)
			{
				wynik.znak = 0;									//dodawanie! 10-(-15)=10+15=25
			}
			else if (a.znak == 1 && b.znak == 0)
			{
				wynik.znak = 1;									//dodawanie! -10-15=-25
			}
			else
			{
				wynik.znak = 0;									//10-15=-5
			}
			//--------------------------Mantysa--------------------------------------
			for (int i = 4080; i >= 0; i--)				//odejmowanie mantys
			{
				if(b.calosc[i]==1 && a.calosc[i]==1)	
					b.calosc[i]=0;						//gdy 1-1 wpisz 0 do a.calosc, w którym na razie trzymany jest wynik
				else if(b.calosc[i]==1 && a.calosc[i]==0)
					b.calosc[i]=1;						//gdy 1-0 wpisz 1 do a.calosc
				else if(b.calosc[i]==0 && a.calosc[i]==0)
					b.calosc[i]=0;						//gdy 0-0 wpisz 0 do a.calosc
				else
				{										//gdy 0-1 potrzebna jest pożyczka
					pozyczka = i;						//zaznaczam miejsce, którym jest potrzebna
					for(int j=pozyczka; j>=0; j--)		//od miejsca pierwszej pożyczki, do końca
					{
						if(b.calosc[j]==1)				//szukaj 1, czyli miejsca z którego można wziąć pożyczkę
						{
							miejsce=j;
							b.calosc[j]=0;				//wypełnij to miejsce 0
							break;						//wyjdź z pętli
						}
					}
					for(int j=pozyczka; j>miejsce; j--)	//od miejsca, gdzie pożyczka była potrzebna
					{									//do miejsca, z którego pożyczka została wzięta, wypełnij wszystko jedynkami
							b.calosc[j]=1;
					}
					b.calosc[pozyczka]=1;				//tam, gdzie pożyczka była potrzena wstaw 1, bo 2-1=1
				}
			}
			/*for(int i=0; i<4081; i++)
			{
				cout << b.calosc[i];
			}//*/
			cout << endl;//*/
			int ilosc = 0;
			for(int i=0; i<4081; i++)
			{
				if(b.calosc[i]==0)
				{
					ilosc++;
				}
				else
					break;
			}
			for(int i=0; i<4080; i++)
			{
				wynik.mantysa[i]=b.calosc[i+ilosc+1];
			}
			for(int i=4080-ilosc; i<4080; i++)	//resztę wypełnij zerami
			{
				wynik.mantysa[i]=0;
			}
			if (b.calosc[0]==0)							//normowanie wyniku, jeśli na pozycji, gdzie w pierwszej liczbie była jedynka,
			{											//a teraz jej nie ma trzeba zmniejszyć wykładnik
				for(int j=0; j<ilosc; j++)				//i to o tyle razy ile jest pozycji z zerami z przodu
				{
					if(wynik.wykladnik[14]==0)			//jeśli ostatnia pozycja jest równa 0, to potrzebna jest pożyczka na tym właśnie miejscu
					{
						pozyczka = 14;					//czyli jak wcześniej - miejsce pożyczki jest ustalone
						for(int i=pozyczka; i>=0; i--)	//teraz trzeba znaleźć jedynkę, którą można zarekwirować
						{
							if(wynik.wykladnik[i]==1)
							{
								miejsce=i;
								wynik.wykladnik[i]=0;
								break;
							}
						}
						for(int i=pozyczka; i>miejsce; i--)
						{
							wynik.wykladnik[i]=1;
						}
						wynik.wykladnik[pozyczka]=1;
					}
					else								//jeśli na ostatnim miejscu jest 1, to ją zamień na zero
					{
						wynik.wykladnik[14]=0;
					}
				}
			}
			//----------------------------------Wyświetlanie-------------------------
			cout << wynik.znak << " ";					//wszystko jasne
			for (int i = 0; i < 15; i++)
				cout << wynik.wykladnik[i];
			cout << " ";
			for (int i = 0; i < 4080; i++)
				cout << wynik.mantysa[i];
			cout << endl;
		}
	}
	return wynik;
}
int128 int128::Dodawanie(int128 a, int128 b)				//większość jak przy odejmowaniu
{
	int128 wynik;
	wynik.znak=0;
	for(int i=0; i<15; i++)							//zerowanie wyniku
	{
		wynik.wykladnik[i]=0;
	}
	for(int i=0; i<4080; i++)
	{
		wynik.mantysa[i]=0;
	}
	int wykla = 0;									//muszę sprawdzić, która liczba jest większa, dlatego przerabiam wykładnik na dziesiętny
	int wyklb = 0;
	int c = 0;
	for (int i = 14; i >= 0; i--)					
	{
		if (a.wykladnik[i] == 1)
		{
			wykla = wykla + pow(2.0, c);
		}
		c++;
	}
	wykla = wykla- 16383;							//zdejmuję obciążenie
	c = 0;
	for (int i = 14; i >= 0; i--)
	{
		if (b.wykladnik[i] == 1)
		{
			wyklb = wyklb + pow(2.0, c);
		}
		c++;
	}
	//cout << wykl << endl;
	wyklb = wyklb - 16383;
	/*cout << endl;
	cout << wykl << endl << endl;//*/
	a.calosc[0]=1;										//zapisuję mantysę z ukrytą jedynką
	b.calosc[0]=1;
	for(int i=1; i<4080; i++)
	{
		a.calosc[i]=a.mantysa[i-1];
	}
	for(int i=1; i<4080; i++)
	{
		b.calosc[i]=b.mantysa[i-1];
	}
	if	(wykla>wyklb)									//liczba a jest większa
	{
		//--------------------------------Znak-----------------------------------
		if (a.znak == 1 && b.znak == 1)					//-15+(-10)=-15-10=-25
		{
			wynik.znak = 1;
		}
		else if (a.znak == 0 && b.znak == 1)			//odejmowanie! 15+(-10)=15-10=5
		{
			wynik.znak = 0;
		}
		else if (a.znak == 1 && b.znak == 0)			//odejmowanie!-15+10=-5
		{
			wynik.znak = 1;
		}
		else											//15+10=25
		{
			wynik.znak = 0;
		}
		//----------------------------------Wykladnik----------------------------
		int ileZer = 0;
		while (wykla>wyklb)								//jak w odejmowaniu - liczę ile zer będzie mi potrzebnych
		{												
			ileZer++;
			wyklb++;
		}
		for(int i = 0; i<15; i++)
			wynik.wykladnik[i]=a.wykladnik[i];			//wykładnik wyniku na tę chwię będzie taki, jak większej liczby. Potem się go unormuje.
		//---------------------------------Mantysa-------------------------------
		short int tym[4080];							//mniejszą liczbę wypełniam zerami tak,
		for (int i = 0; i<4080; i++)					//żeby jej wykladnik był taki sam jak liczby większej
			tym[i] = b.calosc[i];
		for (int i = ileZer; i<4080; i++)
			b.calosc[i] = tym[i-ileZer];
		for (int i = 0; i<ileZer; i++)
			b.calosc[i] = 0;
		short int wynikCalosc[4081];					//potrzebuję zmiennej w której będzie przechowywany wynik. Nie mogę wpisywać od razu do
		for(int i = 0; i <4081; i++)					//mantysy, bo mam ukrytą jedynkę do uwzględnienia
			wynikCalosc[i]=0;
		for (int i = 4079; i >= 0; i--)					//system dodawania, najpierw dodaję do wyniku drugą liczbę
		{
			if (wynikCalosc[i+1] == 2)					//jeśli było przeniesienie, to je uwzględnij
			{
				wynikCalosc[i+1] = 0;
				wynikCalosc[i]++;
			}
			if (wynikCalosc[i+1] == 0 && b.calosc[i] == 0)
			{
				wynikCalosc[i+1] = 0;					//0+0=0
			}
			else if (wynikCalosc[i+1] == 0 && b.calosc[i] == 1)
			{
				wynikCalosc[i+1] = 1;					//0+1=1
			}
			else if (wynikCalosc[i+1] == 1 && b.calosc[i] == 0)
			{
				wynikCalosc[i+1] = 1;					//1+0=1
			}
			else if (wynikCalosc[i+1] == 1 && b.calosc[i] == 1)
			{
				wynikCalosc[i+1] = 0;					//1+1=0 i powiększ następną komórkę o jeden, bo nastąpiło przeniesienie.
				wynikCalosc[i]++;
			}
		}
		for (int i = 4079; i >= 0; i--)								//potem do wyniku dodaję pierwszą liczbę
		{															//takim samym algorytmem jak pierwszą
			if (wynikCalosc[i+1] == 2)
			{
				wynikCalosc[i+1] = 0;
				wynikCalosc[i]++;
			}
			if (wynikCalosc[i+1] == 0 && a.calosc[i] == 0)
			{
				wynikCalosc[i+1] = 0;
			}
			else if (wynikCalosc[i+1] == 0 && a.calosc[i] == 1)
			{
				wynikCalosc[i+1] = 1;
			}
			else if (wynikCalosc[i+1] == 1 && a.calosc[i] == 0)
			{
				wynikCalosc[i+1] = 1;
			}
			else if (wynikCalosc[i+1] == 1 && a.calosc[i] == 1)
			{
				wynikCalosc[i+1] = 0;
				wynikCalosc[i]++;
			}
		}
		/*for (int i = 0; i<4081; i++)
				cout << wynikCalosc[i];
			cout << endl << endl;//*/
		if (wynikCalosc[0]==1/*0 && wynikCalosc[1]==1*/)			//normowanie wyniku, gdy przed przecinkiem jest 10 lub 11, trzeba przesunąć przecinek o jedną pozycję
		{													//co wiąże się ze zmianą wykładnika
			int przeniesienie=1;							//mam dodać jedynkę do wykładnka
			for (int i = 14; i>=0; i--)						//muszę przejrzeć cały wykładnik
			{
				if(wynik.wykladnik[i]==0)					//jeśli w wykładniku jest 0,
				{
					if(przeniesienie==1)					//a przeniesienie było równe 1
					{
						wynik.wykladnik[i]=1;				//to uwzględnij przeniesienie
						przeniesienie--;					//automatycznie je zmniejszając
					}
					else
						wynik.wykladnik[i]=0;				//jeśli go nie było, zapisz po prostu 0
				}
				else										//jeśli w wykładkniku jest 1
				{
					if(przeniesienie==1)					//i przeniesienie jest równe jeden
						wynik.wykladnik[i]=0;				//do wykładnika wpisz 0, ale przeniesienie zostaje
					else
						wynik.wykladnik[i]=1;				//jeśli nie było przeniesienia to wpisz do wykładknika 1
				}
			}
			for(int i = 0; i < 4080; i++)					//zapisz wynik do mantysy, zaraz po pierwszej jedynce
			{
				wynik.mantysa[i]=wynikCalosc[i+1];
			}
		}
		else												//gdy nie będzie zmiany wykdładnika,
		{
			for(int i = 1; i < 4080; i++)					//to wiedząc gdzie jest pierwsza jednyka
			{												//uzupełnij mantysę
				wynik.mantysa[i-1]=wynikCalosc[i+1];
			}
		}
		//----------------------------------Wyświetlanie-------------------------
		cout << wynik.znak << " ";
		for (int i = 0; i < 15; i++)
			cout << wynik.wykladnik[i];
		cout << " ";
		for (int i = 0; i < 4080; i++)
			cout << wynik.mantysa[i];
		cout << endl;
	}
	else											//analogicznie do pierwszej części
	{
		//--------------------------------Znak-----------------------------------
		if (a.znak == 1 && b.znak == 1)				//-10+(-15)=-10-15=-25
		{
			wynik.znak = 1;
		}
		else if (a.znak == 0 && b.znak == 1)		//odejmowanie! 10+(-15)=10-15=-5
		{
			wynik.znak = 1;	
		}
		else if (a.znak == 1 && b.znak == 0)		//odejmowanie! -10+15=-10+15=5
		{
			wynik.znak = 0;
		}
		else										// 10+15=10+15=25
		{
			wynik.znak = 0;
		}
		//----------------------------------Wykladnik----------------------------
		int ileZer = 0;								//jak wyżej z tym, że teraz druga liczba jest większa.
		while (wykla<wyklb)
		{
			ileZer++;
			wykla++;
		}
		for(int i = 0; i<15; i++)
			wynik.wykladnik[i]=b.wykladnik[i];		//teraz wykładnik drugiej liczby jest większy, więc to on będzie zapiswyany jako wynikowy
		//---------------------------------Mantysa-------------------------------
		short int tym[4080];						//dorównywanie liczby do tej z większej wykładnikiem
		for (int i = 0; i<4080; i++)
			tym[i] = a.calosc[i];
		for (int i = ileZer; i<4080; i++)
			a.calosc[i] = tym[i-ileZer];
		//cout << ileZer << endl;
		for (int i = 0; i<ileZer; i++)
			a.calosc[i] = 0;
		/*cout << endl << endl;
		for (int i=0; i<4080; i++)
			cout << a.calosc[i];
		cout << endl << endl;//*/
		short int wynikCalosc[4081];							
		for(int i = 0; i <4081; i++)					//zerowanie wyniku
			wynikCalosc[i]=0;
		for (int i = 4079; i >= 0; i--)					//system dodawania, najpierw dodaję do wyniku drugą liczbę
		{
			if (wynikCalosc[i+1] == 2)					//jeśli było przeniesienie, to je uwzględnij
			{
				wynikCalosc[i+1] = 0;
				wynikCalosc[i]++;
			}
			if (wynikCalosc[i+1] == 0 && a.calosc[i] == 0)
			{
				wynikCalosc[i+1] = 0;					//0+0=0
			}
			else if (wynikCalosc[i+1] == 0 && a.calosc[i] == 1)
			{
				wynikCalosc[i+1] = 1;					//0+1=1
			}
			else if (wynikCalosc[i+1] == 1 && a.calosc[i] == 0)
			{
				wynikCalosc[i+1] = 1;					//1+0=1
			}
			else if (wynikCalosc[i+1] == 1 && a.calosc[i] == 1)
			{
				wynikCalosc[i+1] = 0;					//1+1=0 i powiększ następną komórkę o jeden, bo nastąpiło przeniesienie.
				wynikCalosc[i]++;
			}
		}
		for (int i = 4079; i >= 0; i--)								//potem do wyniku dodaję pierwszą liczbę
		{															//takim samym algorytmem jak pierwszą
			if (wynikCalosc[i+1] == 2)
			{
				wynikCalosc[i+1] = 0;
				wynikCalosc[i]++;
			}
			if (wynikCalosc[i+1] == 0 && b.calosc[i] == 0)
			{
				wynikCalosc[i+1] = 0;
			}
			else if (wynikCalosc[i+1] == 0 && b.calosc[i] == 1)
			{
				wynikCalosc[i+1] = 1;
			}
			else if (wynikCalosc[i+1] == 1 && b.calosc[i] == 0)
			{
				wynikCalosc[i+1] = 1;
			}
			else if (wynikCalosc[i+1] == 1 && b.calosc[i] == 1)
			{
				wynikCalosc[i+1] = 0;
				wynikCalosc[i]++;
			}
		}
		/*for (int i = 0; i<4081; i++)
			cout << wynikCalosc[i];
		cout << endl << endl;//*/
		if (wynikCalosc[0]==1/*0 && wynikCalosc[1]==1*/)
		{
			int przeniesienie=1;
			for (int i = 14; i>=0; i--)
			{
				if(wynik.wykladnik[i]==0)
				{
					if(przeniesienie==1)
					{
						wynik.wykladnik[i]=1;
						przeniesienie--;
					}
					else
						wynik.wykladnik[i]=0;
				}
				else
				{
					if(przeniesienie==1)
						wynik.wykladnik[i]=0;
					else
						wynik.wykladnik[i]=1;
				}
			}
			for(int i = 0; i < 4080; i++)
			{
				wynik.mantysa[i]=wynikCalosc[i+1];
			}
		}
		else
		{
			for(int i = 1; i < 4080; i++)
			{
				wynik.mantysa[i-1]=wynikCalosc[i+1];
			}
		}
	//----------------------------------Wyświetlanie-------------------------
		cout << wynik.znak << " ";
		for (int i = 0; i < 15; i++)
			cout << wynik.wykladnik[i];
		cout << " ";
		for (int i = 0; i < 4080; i++)
			cout << wynik.mantysa[i];
		cout << endl;
	}
	return wynik;
}
/*int int128::WykladnikToDec(int128 a)
{
	int wykl = 0;
	int c = 0;
	for (int i = 14; i >= 0; i--)
	{
		if (wykladnik[i] == 1)
		{
			wykl = wykl + pow(2.0, c);
		}
		c++;
	}
	/*cout << wykl << endl;
	wykl = wykl - 16383;
	cout << wykl << endl;
	cin.ignore();
	return wykl;
}
short int* int128::SumyCzesciowe(short int gdzie[213], short int co[112], int skad) //gdzie - wysyłamy tablicę, do której ma być zapisany wynik, 
																					//co - co do niej wpisujemy, skad - o ile pozycji przesunięta 
																					//jest ta suma
{
	short int temp[213]; //"co" przesunięte i dopełnione zerami
	for (int i = 0; i < 213; i++)
	{
		temp[i] = 0;
	}
	for (int i = 100; i < 212; i++)
	{
		temp[i] = co[i];
	}
	for (int i = 0; i < skad; i++)
	{
		for (int j = 0; j < 213; j++)
		{
			if (i != 212)
			{
				temp[i] = temp[i + 1];
			}
			else
			{
				temp[212] = 0;
			}
		}
	}
	for (int i = 212; i >= 0; i--) // dodawanie do "gdzie" "co" o wyrównanej długości
	{
		if (gdzie[i] == 2)
		{
			gdzie[i] = 0;
			gdzie[i - 1]++;
		}
		if (gdzie[i] == 0 && temp[i] == 0)
		{
			gdzie[i] = 0;
		}
		else if (gdzie[i] == 0 && temp[i] == 1)
		{
			gdzie[i] = 1;
		}
		else if (gdzie[i] == 1 && temp[i] == 0)
		{
			gdzie[i] = 1;
		}
		else if (gdzie[i] == 1 && temp[i] == 1)
		{
			gdzie[i] = 0;
			gdzie[i - 1]++;
			if (i == 0)
			{
				przeniesieniesumy = 1;
			}
		}
	}
	/*cout << "Suma częściowa: ";
	for (int i = 0; i < 213; i++)
	{
		cout << gdzie[i];
	}
	cout << endl;
	system("pause");
	return gdzie;
}
int128 int128::Mnozenie128(int128 a, int128 b)
{
	int128 wynik;
	if (a.znak == 1 && b.znak == 1)
	{
		wynik.znak = 1;
	}
	else if (a.znak == 0 && b.znak == 1)
	{
		wynik.znak = 1;
	}
	else if (a.znak == 1 && b.znak == 0)
	{
		wynik.znak = 1;
	}
	else
	{
		wynik.znak = 0;
	}
	short int *sumy = new short int[213];
	for (int i = 0; i < 213; i++)
	{
		sumy[i] = 0;
	}
	int wykl, wyklTemp;
	wykl = a.WykladnikToDec(a);
	wyklTemp = b.WykladnikToDec(b);
	wykl = wykl + wyklTemp;
	int c = 0;
	/*for (int i = 112; i >= 0; i--)
	{
		cout << b.calosc[i];
	}
	cout << endl;
	for (int i = 112; i >= 0; i--)
	{
		cout << a.calosc[i];
	}
	cout << endl;
	cin.ignore();
	for (int i = 112; i >= 0; i--)
	{
		if (b.mantysa[i] == 1)
		{
			sumy = SumyCzesciowe(sumy, a.mantysa, c);
		}
		c++;
	}
	cout << "Wynik sumy częściowej: ";
	for (int i = 0; i < 213; i++)
	{
		cout << sumy[i];
	}
	cout << endl;
	system("pause");
	return wynik;
}
int128 int128::Odejmowanie128(int128 a, int128 b)
{
	int128 wynik;

	return wynik;
}
int128 int128::Dodawanie128(int128 a, int128 b)
{
	int128 wynik;
	if (a.znak == 1 && b.znak == 1)
	{
		//
	}
	else if (a.znak == 0 && b.znak == 1)
	{
		wynik = Odejmowanie128(a, b);
		return wynik;
	}
	else if (a.znak == 1 && b.znak == 0)
	{
		wynik = Odejmowanie128(a, b);
		return wynik;
	}

	return wynik;
}*/
