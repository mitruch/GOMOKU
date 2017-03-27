#pragma once

#include <string>
#include <iomanip>
#include <iostream>

#include "rozmieszczenie.h"

#define MAX 15  //rozmiar planszy
#define gom	5	//ilosc pionkow w linii potrzebna do wygrania

using namespace std;

class plansza;

class gracz {
protected:
	string name;
	bool wygrana;
	char pionek;
	int licznik_ruchow;

public:
	rozmieszczenie *glowa;
	rozmieszczenie *wsk;

	//metoda obslugujaca jeden ruch gracza
	virtual int ruch(plansza &pln) { return 0; }; 

	bool get_wygrana() { return wygrana; };
	string get_name() { return name; };
	char get_pionek() { return pionek; };
	int get_licznik_ruchow() { return licznik_ruchow; };

	void set_name(string name_s) { name = name_s; };
	void set_wygrana(bool wygrana_s) { wygrana = wygrana_s; };
	void set_licznik_ruchow(int licznik_ruchow_s) { //dodatkowa kontrola poprawnosci danych
		if (licznik_ruchow_s < 0)
			licznik_ruchow = 0;
		else
			licznik_ruchow = licznik_ruchow_s; 
	}

	//konstruktor z argumentami
	gracz(string name_k, char pionek_k) :wygrana(false), glowa(NULL), wsk(NULL), licznik_ruchow(0) {					
		name = name_k;
		pionek = pionek_k;
	}

	//konstruktor kopiujacy
	gracz(gracz &kopia) {
		glowa = kopia.glowa;
		wsk = kopia.wsk;
		name = kopia.name;
		wygrana = kopia.wygrana;
		pionek = kopia.pionek;
	}

	//destruktor rozpoczynajacy usuwanie listy dynamicznej rozmieszczen pionkow
	virtual ~gracz() { delete glowa; };
};

class plansza {
	char pole[MAX][MAX];
public:

	//konstruktor domyslny
	plansza() {
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				pole[i][j] = 0;
	}

	//metoda wypisujaca plansze
	void wypisz();

	// metoda sprawdzajaca czy dany gracz juz wygral
	int czy_wygrana(gracz*); 

	//metoda sprawdzajaca czy podane pole nie jest juz zajete 
	bool czy_zajete(int czy_wiersz, char czy_kolumna) {
		if (pole[czy_wiersz - 1][(czy_kolumna - 97)] == 0)
			return false;
		else return true;
	}

	//metoda aktualizujaca zawartosc planszy
	void aktualizuj(int pionek, int wiersz_akt, char kolumna_akt) {
		pole[(wiersz_akt - 1)][(kolumna_akt - 97)] = pionek;
		wypisz();
	}

};