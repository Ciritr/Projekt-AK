#include "stdafx.h"

int main()
{
	//_CRT_SECURE_NO_WARNINGS;
	setlocale(LC_ALL, "Polish");
	int128 proba;
	int128 liczba;
	cout << "Pierwsza liczba - proba." << endl;
	proba.StringToBin();
	proba.Ulamek();
	system("pause");
	cout << "Druga liczba - liczba." << endl;
	liczba.StringToBin();
	liczba.Ulamek();
	system("pause");
	int128 wynik;
	wynik = wynik.Mnozenie128(proba, liczba);
	return 0;
}