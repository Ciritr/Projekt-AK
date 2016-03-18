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
	cout << "Podaj œcie¿kê pliku." << endl;
	cin >> sciezka;
	system("CLS");
	//sciezka = "d:/liczba.txt";
	fstream plik(sciezka.c_str(), ios::in);
	getline(plik, bufor);
	plik.close();
	system("CLS");
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
	//----------------------------------CA£KOWITA-------------------------------------
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
	//------------------------------------U£AMEK----------------------------------------
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
void int128::Ulamek()
{
	int przecinek_binarny = 0;
	for (int i = 8191; i >= 0; i--)
	{
		if (tab[i] == 1)
		{
			przecinek_binarny = i + 1;
			break;
		}
	}
	//cout << przecinek_binarny << endl;
	int siterator = 0;
	for (int i = przecinek + 1; i < 2047; i++)
	{
		if (tabchar[i] < '0' || tabchar[i] > '9')
		{
			siterator = i;
			break;
		}
	}
	short int supertablica[2048];
	int rozmiar_tablicy = 0;
	for (int i = przecinek; i < siterator; i++)
	{
		supertablica[rozmiar_tablicy] = tabchar[i] - '0';
		rozmiar_tablicy++;
	}
	int wysw = siterator - przecinek;						//6-3-1=2
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
	for (int i = 8192 - przecinek_binarny; i >= 0; i--) // nie minus przecinek dzisiêtny, a binarny
	{
		twysw = wysw - 1;
		for (int j = wysw - 1; j >= 0; j--)
		{
			if (j == 0)
			{
				supertablica[0] *= 2;
				if (supertablica[twysw + 1] >= 10)
				{
					supertablica[twysw]++;
					supertablica[twysw + 1] -= 10;
				}
				if (supertablica[0] >= 10)
				{
					przeniesienie++;
					supertablica[0] -= 10;
				}
			}
			else
			{
				supertablica[twysw] *= 2;
				if (supertablica[twysw + 1] >= 10)
				{
					supertablica[twysw]++;
					supertablica[twysw + 1] -= 10;
				}
				twysw--;
			}
		}
		if (przeniesienie)
		{
			temp[k] = 1;
			k++;
		}
		else
		{
			temp[k] = 0;
			k++;
		}
		przeniesienie = 0;
	}
	//cout << wysw << endl;
	//--------------------------------WYŒWIETLANIE--------------------------------------
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
	//cout << "Liczba binarnie wygl¹da: " << endl;
	int f = 0;
	for (int j = przecinek_binarny - 1; j >= 0; j--)
	{
		wynikbinarnie[f] = tab[j];
		//cout << wynikbinarnie[f];
		f++;
	}
	f = 0;
	//cout << ",";
	for (int i = przecinek_binarny; i<8192; i++)
	{
		wynikbinarnie[i] = temp[f];
		//cout << wynikbinarnie[i];
		f++;
	}
	cout << endl;
	int potega = 0;
	if (przecinek_binarny>1)
	{
		potega = przecinek_binarny;
		//cout << potega << endl;
	}
	else if (przecinek_binarny == 1)
		potega = 0;
	else if (przecinek_binarny == 0)
	{
		for (int j = 0; j<8192; j++)
		{
			if (wynikbinarnie[j] == 1)
			{
				potega = 0 - j - 1;					//ilosc zer w zapisie liczby binarniej
				//cout << potega << endl;
				break;
			}
		}
	}
	//cout << potega << endl;
	//--------------------------WYK£ADNIK-------------------------------
	wykladnik[0] = 1;
	for (int i = 1; i<15; i++)
	{
		wykladnik[i] = 0;
	}
	int obciazenie[15];
	if (potega<0)													//dla ujemnych potêg 0.0000000cos
	{
		for (int i = 0; i<15; i++)
		{
			obciazenie[i] = 0;
		}
		int p = abs(potega);
		int c = 0;
		do
		{
			obciazenie[c] = p % 2;
			p /= 2;
			c++;
		} while (p != 0);
		for (int i = 0; i<15; i++)
		{
			if (obciazenie[i] == 1)
				obciazenie[i] = 0;
			else
				obciazenie[i] = 1;
		}
		wykladnik[0] = 0;
		for (int i = 1; i<15; i++)
		{
			wykladnik[i] = 1;
		}
		int u = 0;
		for (int i = 14; i>0; i--)
		{
			wykladnik[i] = obciazenie[u];
			u++;
		}
	}
	else if (potega == 0)						//dla zerowej potêgi, w przypadku 1,cos
	{
		wykladnik[0] = 0;
		for (int i = 1; i<15; i++)
		{
			wykladnik[i] = 1;
		}
	}
	else if (potega >= 1)									//dla normalnych liczb
	{
		for (int i = 0; i<15; i++)
		{
			obciazenie[i] = 0;
		}
		int p = potega - 2;
		int c = 0;
		do
		{
			obciazenie[c] = p % 2;
			p /= 2;
			c++;
		} while (p != 0);
		wykladnik[0] = 1;
		int u = 0;
		for (int i = 14; i>0; i--)
		{
			wykladnik[i] = obciazenie[u];
			u++;
		}
	}
	//--------------------------MANTYSA-----------------------------------
	if (potega >= 0)
	{
		for (int i = 0; i<112; i++)
		{
			mantysa[i] = wynikbinarnie[i + 1];
		}
	}
	else
	{
		for (int i = 0; i<112; i++)
		{
			mantysa[i] = wynikbinarnie[i - potega];
		}
	}
	//----------------------WYŒWIETLANIE---------------------------------
	cout << "Liczba przekonwertowana IEEE 754 z obci¹¿eniem 2^15-1: " << endl;
	cout << znak << " ";
	for (int i = 0; i<15; i++)
		cout << wykladnik[i];
	cout << " ";
	for (int i = 0; i<112; i++)
		cout << mantysa[i];
	cout << endl;
}
void int128::BintoDec()
{
	char z;
	string liczba;
	int rozmiar = 1;
	int pozycja = 0;
	short int *binpotega = new short int[rozmiar];
	if (znak == 1)
		z = '-';
	long double potegaDwojki = 0;
	if (wykladnik[0] == 0)													//dla ujemnych potêg 0.0000000cos
	{
		//#pragma omp parallel
		//#pragma omp for schedule (dynamic,1) 
		for (int i = 1; i<15; i++)
		{
			if (wykladnik[i] == 0)
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
		for (int i = 0; i<rozmiar; i++)
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
		for (int i = 0; i <rozmiar; i++)
		{
			if (binpotega[i] == 1)
				potegaDwojki = potegaDwojki + pow(2.0, i);
		}
		potegaDwojki = 0 - potegaDwojki;
		//cout << potegaDwojki << endl;
	}
	else if (wykladnik[0] == 1)						//na koñcu zamiany na potêgê trzeba dodaæ 1!
	{
		for (int i = 1; i<15; i++)
		{
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
		potegaDwojki++;							//to z tego tam na pocz¹tku
		//cout << potegaDwojki << endl;
	}
	calosc[0] = 1;
	for (int i = 0; i<112; i++)
	{
		calosc[i + 1] = mantysa[i];
	}
	int rozmiarCalkowita = 0;
	int rozmiarUlamek = 0;
	if (potegaDwojki>0)
	{
		rozmiarCalkowita = potegaDwojki + 1;
		rozmiarUlamek = 113 - potegaDwojki;
	}
	else
	{
		rozmiarUlamek = 112 + abs(potegaDwojki);
	}
	short int *calkowita = new short int[rozmiarCalkowita];
	short int *ulamek = new short int[rozmiarUlamek];
	//cout << rozmiarCalkowita << " " << rozmiarUlamek << endl;
	//cin.ignore();
	int iloscZer = abs(potegaDwojki) - 1;
	if (potegaDwojki>0)
	{
		for (int i = 0; i<rozmiarCalkowita; i++)
		{
			calkowita[i] = calosc[i];
			//cout << calkowita[i];
		}
		//cout << ",";
		for (int i = rozmiarCalkowita; i<rozmiarUlamek; i++)
		{
			ulamek[i - rozmiarCalkowita] = calosc[i];
			//cout << ulamek[i];
		}
	}
	else if (potegaDwojki == 0)
	{
		rozmiarCalkowita = 1;
		calkowita[0] = 1;
		//cout << calkowita[0] << ",";
		for (int i = 0; i<rozmiarUlamek; i++)
		{
			ulamek[i] = calosc[i - iloscZer];
			//cout << ulamek[i];
		}
	}
	else
	{
		//cout << "0,";
		for (int i = 0; i<iloscZer; i++)
		{
			ulamek[i] = 0;
			//cout << ulamek[i];
		}
		for (int i = iloscZer; i<rozmiarUlamek; i++)
		{
			ulamek[i] = calosc[i - iloscZer];
			//cout << ulamek[i];
		}

	}
	//cin.ignore();
	//------------Tu nast¹pi przerobienie na stringa czêœci ca³kowitej----------------
	//cout << endl;
	char *tablicaBitow = new char[rozmiarCalkowita + 1];
	for (int i = 0; i<rozmiarCalkowita; i++)
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
		bitowaCalosc = bitowaCalosc + tablicaBitow[i];
	}

	//cout << bitowaCalosc << endl;
	string dziesietnaCalosc;
	int licznik1, cyfraBinarna, przeniesienie, schemat;
	cout << endl;
	dziesietnaCalosc = "0"; licznik1 = 0;
	while ((licznik1 < bitowaCalosc.length()) && ((bitowaCalosc[licznik1] == '0') || (bitowaCalosc[licznik1] == '1')))
	{
		przeniesienie = 0;									// Przeniesienie
		cyfraBinarna = bitowaCalosc[licznik1] - 48;			// Cyfra binarna
		for (int j = dziesietnaCalosc.length() - 1; j >= 0; j--)
		{													// Schemat Hornera
			schemat = 2 * (dziesietnaCalosc[j] - 48) + cyfraBinarna + przeniesienie;
			cyfraBinarna = 0;									// Wyznaczamy przeniesienie do nastêpnej kolumny
			przeniesienie = schemat / 10;						// Cyfrê wynikow¹ zapisujemy w miejscu docelowym
			dziesietnaCalosc[j] = (char)((schemat % 10) + 48);
			// Jeœli po wyczerpaniu cyfr dziesietnaCalosc przeniesienie p ma wartoœæ
			// wiêksz¹ od zera, to jest ono równe pierwszej cyfrze
			if (!j && przeniesienie) dziesietnaCalosc = (char)(przeniesienie + 48) + dziesietnaCalosc;
		};													// Nastêpna cyfra binarna
		licznik1++;
	};

	//------------------------A tu miejsce na konwersjê przecinka;
	char *tablicaUlamkow = new char[rozmiarUlamek - rozmiarCalkowita];
	for (int i = 0; i<rozmiarUlamek - rozmiarCalkowita; i++)
	{
		tablicaUlamkow[i] = ulamek[i] + '0';
	}
	/*for(int i = 0; i<rozmiarUlamek-rozmiarCalkowita; i++)
	{
	cout << tablicaUlamkow[i];
	}
	cout << endl;*/
	string bitowyUlamek;
	for (int i = 0; i<rozmiarUlamek - rozmiarCalkowita; i++)
	{
		bitowyUlamek = bitowyUlamek + tablicaUlamkow[i];
	}

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
			cyfraBinarna = 0;									// Wyznaczamy przeniesienie do nastêpnej kolumny
			przeniesienie = schemat / 10;						// Cyfrê wynikow¹ zapisujemy w miejscu docelowym
			dziesietnyUlamek[j] = (char)((schemat % 10) + 48);
			// Jeœli po wyczerpaniu cyfr dziesietnyUlamek przeniesienie p ma wartoœæ
			// wiêksz¹ od zera, to jest ono równe pierwszej cyfrze
			if (!j && przeniesienie) dziesietnyUlamek = (char)(przeniesienie + 48) + dziesietnyUlamek;
		};													// Nastêpna cyfra binarna
		licznik1++;
	};
	/*teraz wystarczy podzieliæ u³amek przez 1/(2^liczba wystêpuj¹cych miejsc po przecinku), ale nie mam pojêcia jak to zrobiæ.
	Przesuniêcie bitowe?
	wszystko o rozmiarUlamek
	trzebaby by³o zdefiniowaæ funkcjê podziel na 2 i wykonaæ j¹ rozmiarUlamek razy.
	2 problemy:
	1. podzieliæ trzeba by by³o ca³¹ liczbê
	2. duuuuuuuuuu¿o zabawy
	string w tablicê shortów
	zaimplemenowaæ dzielenie
	a potem wrzuciæ to w pêtle
	*/
	char *doKonwersji = new char[dziesietnyUlamek.length() + 1];
	short int *dzielonyUlamek = new short int[dziesietnyUlamek.length()];
	strcpy(doKonwersji, dziesietnyUlamek.c_str());
	/*cin.ignore();
	for(int i=0; i<dziesietnyUlamek.length()+1; i++)
	{
	cout << doKonwersji[i];
	}
	cin.ignore();*/
	for (int i = 0; i<dziesietnyUlamek.length(); i++)
	{
		dzielonyUlamek[i] = doKonwersji[i] - 48;
	}
	/*for(int i=0; i<dziesietnyUlamek.length(); i++)
	{
	cout << dzielonyUlamek[i];
	}
	cin.ignore();*/
	for (int i = 0; i<dziesietnyUlamek.length(); i++)				//podziel na dwa tyle razy jak ile jest cyfr
	{
		for (int j = 0; j<dziesietnyUlamek.length(); j++)
		{
			if (dzielonyUlamek[j] == 0)							//bez tego ifa dzia³a³o z dok³adnoœci¹ do 0,01 dla przyk³adowej liczby
			{													//nie wiem, jak dla innych. A teraz wogóle nie dziala.
				dzielonyUlamek[j] = 0;
			}
			else
			{
				dzielonyUlamek[j] = dzielonyUlamek[j] / 2;
				if ((j - 1) == dziesietnyUlamek.length())
					break;
				dzielonyUlamek[j + 1] = dzielonyUlamek[j + 1] + 10 * (dzielonyUlamek[j + 1] % 2);
			}
		}
		if (dzielonyUlamek[0] == 0)
		{
			for (int licznik2 = 0; licznik2<dziesietnyUlamek.length(); licznik2++)
			{
				dzielonyUlamek[licznik2] = dzielonyUlamek[licznik2 + 1];
			}
		}
	}
	//cout << dziesietnyUlamek.length() << endl;
	//cout << dziesietnyUlamek << enld;
	/*for(int i=0; i<dziesietnyUlamek.length(); i++)
	{
	cout << dzielonyUlamek[i];
	}
	cout << endl;
	cin.ignore();*/
	//------------------------Wyœwietlanie-------------------------

	cout << "I z powrotem na dziesiêtny:\n" << dziesietnaCalosc << ".";
	/*for(int i=0; i<dziesietnyUlamek.length(); i++)
	{
	cout << dzielonyUlamek[i];
	}
	cout << endl;*/














	/*string dziesietnaCalosc;
	int przeniesienie, cyfraBinarna, schemat, licznik1;				//p, c, s, i
	dziesietnaCalosc="0";
	licznik1=0;
	cout << bitowaCalosc.length() << endl;
	cout << "wpisz liczbe binarie:" << endl;
	cin >> bitowaCalosc;
	cout << endl;
	cout << bitowaCalosc.length() << endl;
	cout << dziesietnaCalosc.length() << endl;
	while((licznik1<bitowaCalosc.length()) && ((bitowaCalosc[licznik1]=='0') || (bitowaCalosc[licznik1]=='1')))
	{
	przeniesienie=0;
	cyfraBinarna=bitowaCalosc[licznik1]-48;
	for(int j=dziesietnaCalosc.length()-1; j>=0; j--)
	{
	schemat=2*(bitowaCalosc[j]-48)+cyfraBinarna+przeniesienie;
	cyfraBinarna=0;
	przeniesienie=schemat/10;
	dziesietnaCalosc[j]=(char)((schemat%10)+48);
	if(!j && przeniesienie)
	dziesietnaCalosc=(char) (przeniesienie+48)+dziesietnaCalosc;
	}
	licznik1++;
	}
	cout << dziesietnaCalosc << endl;
	cin.ignore();*/















	/*
	int p=abs(potega)+1;
	int c = 0;
	do
	{
	obciazenie[c] =p % 2;
	p /= 2;
	c++;
	}while (p != 0);
	for (int i=0; i<1023; i++)
	{
	if (obciazenie[i]==1)
	obciazenie[i] = 0;
	else
	obciazenie[i] = 1;
	}
	wykladnik[0]=0;
	for (int i=1; i<1023; i++)
	{
	wykladnik[i] = 1;
	}
	int u = 0;
	for (int i=1022; i>0; i--)
	{
	wykladnik[i] = obciazenie[u];
	u++;
	}
	}
	else if (potega == 0)						//dla zerowej potêgi, w przypadku 1,cos
	{
	wykladnik[0]=1;
	for (int i=1; i<1023; i++)
	{
	wykladnik[i] = 0;
	}
	}
	else										//dla normalnych liczb
	{
	for (int i=0; i<1023; i++)
	{
	obciazenie[i] = 0;
	}
	int p=potega;
	int c = 0;
	do
	{
	obciazenie[c] =p % 2;
	p /= 2;
	c++;
	}while (p != 0);
	wykladnik[0]=1;
	int u = 0;
	for (int i=1022; i>0; i--)
	{
	wykladnik[i] = obciazenie[u];
	u++;
	}
	}*/
}
int int128::WykladnikToDec(int128 a)
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
	cin.ignore();*/
	return wykl;
}
short int* int128::SumyCzesciowe(short int gdzie[213], short int co[112], int skad) //gdzie - wysy³amy tablicê, do której ma byæ zapisany wynik, 
																					//co - co do niej wpisujemy, skad - o ile pozycji przesuniêta 
																					//jest ta suma
{
	short int temp[213]; //"co" przesuniête i dope³nione zerami
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
	for (int i = 212; i >= 0; i--) // dodawanie do "gdzie" "co" o wyrównanej d³ugoœci
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
	/*cout << "Suma czêœciowa: ";
	for (int i = 0; i < 213; i++)
	{
		cout << gdzie[i];
	}
	cout << endl;
	system("pause");*/
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
	cin.ignore();*/
	for (int i = 112; i >= 0; i--)
	{
		if (b.mantysa[i] == 1)
		{
			sumy = SumyCzesciowe(sumy, a.mantysa, c);
		}
		c++;
	}
	cout << "Wynik sumy czêœciowej: ";
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
}