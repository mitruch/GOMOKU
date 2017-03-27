#include "czlowiek.h"

//metoda wyboru pol
int czlowiek::ruch(plansza &P1) {

	bool wprowadzanie;

	int wiersz_wprowadzanie;
	char kolumna_wprowadzanie;

	do {
		cout << "\nPodaj wiersz: " << endl;
		//wczytywanie adresu wiersza od uzytkownika z kontrola poprawnosci danych
		while (scanf("%d", &wiersz_wprowadzanie) != 1 || wiersz_wprowadzanie > MAX || wiersz_wprowadzanie < 0 || getchar() != '\n'){
			printf("\nMusisz podac cyfre z przedzialu (1-15) ! Sprobuj jeszcze raz.\nPodaj wiersz: ");
			while (getchar() != '\n')
				;	//czyszczenie bufora klawiatury
		}

		if (wiersz_wprowadzanie == 0) //informacja o checi zakonczenia programu przez uzytkownika
			return 0; 

		cout << "\nPodaj kolumne: " << endl;
		//wczytywanie adresu kolumny od uzytkownika z kontrola poprawnosci danych
		while (scanf("%c", &kolumna_wprowadzanie) != 1 || kolumna_wprowadzanie < 'a' || kolumna_wprowadzanie > 'o' || isalpha(kolumna_wprowadzanie) == 0 || getchar() != '\n'){
			printf("\nMusisz podac mala litere alfabetu (od 'a' do 'o') ! Sprobuj jeszcze raz.\nPodaj kolumne: ");
			while (getchar() != '\n')
				;	//czyszczenie bufora klawiatury
		}

		wprowadzanie = false;

		if (P1.czy_zajete(wiersz_wprowadzanie, kolumna_wprowadzanie) == true) {
			wprowadzanie = true;
			cout << "\nTo pole jest zajete !\nWybierz jeszcze raz: " << endl;
		}
		else {
			P1.aktualizuj(pionek, wiersz_wprowadzanie, kolumna_wprowadzanie); //aktualizacja planszy

			//tworzenie listy dynamicznej zapamietujacej historie ruchow czlowieka
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

	return 1; //informacja o kontynuowaniu gry
}