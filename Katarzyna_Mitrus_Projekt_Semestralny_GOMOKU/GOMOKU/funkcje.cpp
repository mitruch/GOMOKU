#include "funkcje.h"

//funkcja wczytujaca zapis z pliku
gracz* wczytywanie(ifstream &wczyt, plansza &pln) {

	int czytaj_int;
	char czytaj_char;
	string wczyt_name;
	gracz* player;

	wczyt >> wczyt_name;	//wczytywanie nazwy gracza
	wczyt >> czytaj_char;	//wczytywanie pionka
	
	if (wczyt.eof()) {      //sprawdzanie czy zapis istnieje
		cout << "\nBrak zapisu gry!" << endl;
		cout << "\nKoniec programu." << endl;
		system("PAUSE");
		exit(0);
	}

	//tworzenie nowego obiektu
	if (wczyt_name == "KOMPUTER")
		player = new komputer();
	else
		player = new czlowiek(wczyt_name, czytaj_char);

	wczyt >> czytaj_int;  //wczytywanie liczby ruchow
	player->set_licznik_ruchow(czytaj_int); //ustawianie licznika ruchow z kontrola poprawnosci

	for (int i = 0;i < (player->get_licznik_ruchow());i++) {
		wczyt >> czytaj_int;	//wczytywanie adresu wiersza
		wczyt >> czytaj_char;	//wczytywanie adresu kolumny

		//uzupelnianie historii ruchow
		if (player->glowa == NULL) {
			player->glowa = player->wsk = new rozmieszczenie();
			player->wsk->set_wiersz(czytaj_int); //usatwianie wierszy + kontrola danych przez seter (jesli blad ustawia adres na 0)
			player->wsk->set_kolumna(czytaj_char); //ustawianie kolumn + kontrola danych przez seter (jesli blad ustawia adres na 0)
			if (player->wsk->get_kolumna() == 0 || player->wsk->get_wiersz() == 0) {
				//wyjscie awaryjne w przypadku bledych danych w pliku
				delete player->glowa;
				cout << "\nDane uszkodzone" << endl;
				cout << "\nKoniec programu.\n" << endl;
				exit(0);
			}
		}
		else {
			player->wsk->nast = new rozmieszczenie();	
			player->wsk->nast->set_wiersz(czytaj_int); //ustawianie wierszy + kontrola danych przez seter (jesli blad ustawia adres na 0)
			player->wsk->nast->set_kolumna(czytaj_char); //ustawianie kolumn + kontrola danych przez seter (jesli blad ustawia adres na 0)
			if (player->wsk->nast->get_kolumna() == 0 || player->wsk->nast->get_wiersz() == 0) {
				//wyjscie awaryjne w przypadku bledych danych w pliku
				delete player->glowa;
				cout << "\nDane uszkodzone" << endl;
				cout << "\nKoniec programu.\n" << endl;
				exit(0);
			}
			player->wsk = player->wsk->nast;
		}
		pln.aktualizuj((player->get_pionek()), czytaj_int, czytaj_char); //aktualizacja planszy
	}

	return player;  //zwrocenie wskaznika do nowo utworzonego gracza

}


void zapisywanie(ofstream &zapisz, gracz *player) {

	player->wsk = player->glowa;
	zapisz << player->get_name() << endl;				//zapis nazwy gracza
	zapisz << player->get_pionek() << endl;				//zapis pionka
	zapisz << player->get_licznik_ruchow() << endl;		//zapis liczby ruchow
	while (player->wsk != NULL) {						//zapis historii ruchow 
		zapisz << player->wsk->get_wiersz() << endl;
		zapisz << player->wsk->get_kolumna() << endl;
		player->wsk = player->wsk->nast;
	}
}

