#include "komputer.h"

//metoda wykonujaca ruch w grze przez komputer
int komputer::ruch(plansza &P1) {

	bool wprowadzanie;

	int wiersz_wprowadzanie;
	char kolumna_wprowadzanie;

	do {
		wiersz_wprowadzanie = losuj();		//losowanie adresu wiersza
		kolumna_wprowadzanie = losuj() + 96; //losowanie adresu kolumny i przeksztalcenie na litere

		wprowadzanie = P1.czy_zajete(wiersz_wprowadzanie, kolumna_wprowadzanie); //sprawdzanie czy wylosowane pole nie jest juz zajete

		if (wprowadzanie == false) {
			P1.aktualizuj(pionek, wiersz_wprowadzanie, kolumna_wprowadzanie);

			//tworzenie listy dynamicznej zapamietujacej historie ruchow komputera
			if (glowa == NULL) {
				glowa = wsk = new rozmieszczenie(wiersz_wprowadzanie, kolumna_wprowadzanie);
				licznik_ruchow++;
			}
			else {
				wsk->nast = new rozmieszczenie(wiersz_wprowadzanie, kolumna_wprowadzanie);
				wsk = wsk->nast;
				licznik_ruchow++;
			}
		}
	} while (wprowadzanie);

	return 1; //komputer nie ma mozliwosci przerywania gry, wiec zawsze zwraca 1
}