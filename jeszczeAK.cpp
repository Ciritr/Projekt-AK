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
	//proba.BintoDec();
	system("pause");
	cout << "Druga liczba - liczba." << endl;
	liczba.StringToBin();
	liczba.Ulamek();
	system("pause");
	int128 wynik;
	system("CLS");
	char zo;
	cout << "Jak¹ operacjê chcesz wykonaæ?" << endl 
		<< " +		dodawanie" << endl
		<< " -		odejmowanie" << endl
		<< " *		mno¿enie" << endl
		<< "WprowadŸ znak" << endl;
	cin >> zo;
	switch(zo)
	{
	case '+':wynik = wynik.Dodawanie(proba, liczba); break;
	case '-':wynik = wynik.Odejmowanie(proba, liczba); break;
	case '*':wynik = wynik.Mnozenie(proba, liczba); break;
	default: cout << "Nie wiem, co mam zrobiæ z " << zo << ", wiêc koñczê program" << endl;
	}
	wynik.BintoDec();
	cin.ignore();
	cin.ignore();//*/
	return 0;
}