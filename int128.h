#pragma once
#include <string>
class int128
{
private:
	short int tab[8192];
	short int temp[8192];
	int znak;
	int przeniesieniesumy;
	short int wykladnik[15];
	short int mantysa[4080];
	short int wynikbinarnie[8192];
	short int calosc[4081];
	int zero;
public:
	int128();
	~int128();
	int przecinek;
	int stop;
	char tabchar[2048];
	void StringToBin();
	void x10(int128 wynik, int ile);
	void p10(int128 wynik, int ile);
	int128 PrawdziweX10(int128 wynik);
	int128 PrawdziweP10(int128 wynik);
	int128 Dodaj(int128 t1, int128 t2);
	int128 DodajT(int128 t1, int128 t2);
	void DodajDoTaba(int128 t1);
	void DodajDoTempa(int128 t1);
	void Ulamek();
	void Rownaj();
	void BintoDec();
	int128 Mnozenie(int128 a, int128 b);
	int128 Dodawanie(int128 a, int128 b);
	int128 Odejmowanie(int128 a, int128 b);
	//int128 Dodawanie128(int128 a, int128 b);
	//int128 Mnozenie128(int128 a, int128 b);
	//int128 Odejmowanie128(int128 a, int128 b);
	//int WykladnikToDec(int128 a);
	//short int* SumyCzesciowe(short int gdzie[213], short int co[2032], int skad);
};

