#pragma once

using namespace std;

class rozmieszczenie {
private:
	int wiersz;
	char kolumna;
public:
	rozmieszczenie* nast; //wskaznik do obiektu listy dynamicznej przechowujacej historie ruchow

	int get_wiersz() { return wiersz; };
	char get_kolumna() { return kolumna; };

	void set_wiersz(int wiersz_s) {			//zapobiega wystartowaniu programu z nieprawidlowymi danymi
		if (wiersz_s < 1 || wiersz_s>15) {
			wiersz_s = 0; //informacja o uszkodzonych danych
		}
		wiersz = wiersz_s; 
	};
	void set_kolumna(char kolumna_s) {	
		if (kolumna_s < 'a' || kolumna_s>'o') {
			kolumna_s=0; //informacja o uszkodzonych danych
		}
		kolumna = kolumna_s;
	};

	//konstruktor domyslny / z argumentami
	rozmieszczenie(int wiersz_k=1, char kolumna_k='a') : wiersz(wiersz_k), kolumna(kolumna_k), nast(NULL) {};

	//destruktor usuwajacy rekurencyjnie kolejne elementy listy dynamicznej
	~rozmieszczenie() { delete nast; };

};