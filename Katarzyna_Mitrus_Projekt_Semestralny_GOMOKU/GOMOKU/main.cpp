#include "gracz.h"
#include "czlowiek.h"
#include "komputer.h"
#include "funkcje.h"

#include <stdlib.h>

using namespace std;

int main() {

	plansza plansza_gomoku;  
	gracz *G1;
	gracz *G2;

	char wybor_start;
	char wybor_trybu;
	bool decyzja_1;

	cout << "\tGRA GOMOKU" << endl;
	cout << "Autor programu: Katarzyna Mitrus\n" << endl;

	do {
		bool decyzja_2;
		decyzja_1 = true;
		cout << "\nNOWA GRA wcisnij (n)" << endl;
		cout << "WCZYTAJ OSTATNIO ZAPISANA GRE wcisnij (w)" << endl;
		cout << "POKAZ STATYSTYKI wcisnij (s)" << endl;
		cout << "WYJSCIE Z GRY wcisnij (0)" << endl;
		cout << "\nKazdy wybor zatwierdz klawiszem <enter>" << endl;
		cin >> wybor_start;

		switch (wybor_start) {

			//NOWA GRA
			case'n': { 
				do {
					cout << "\nWybierz tryb gry:" << endl;
					cout << "Wcisnij (1) by grac [z komputerem]" << endl;
					cout << "Wcisnij (2) by grac [z drugim graczem]" << endl;
					cout << "Aby zakonczyc program wcisnij (0)" << endl;
					cin >> wybor_trybu;

					decyzja_2 = true;
					switch (wybor_trybu) {
						//GRA Z KOMPUTEREM
						case '1': {
							string nick1;
							cout << "\nPodaj swoj nick: ";
							cin >> nick1;
							G1 = new  czlowiek(nick1);
							G2 = new komputer();
							break;
						}
						//GRA Z CZLOWIEKIEM
						case '2': {
							string nick1;
							string nick2;
							cout << "\nPodaj nick pierwszego gracza: ";
							cin >> nick1;
							G1 = new  czlowiek(nick1);
							cout << "Podaj nick drugiego gracza: ";
							cin >> nick2;
							G2 = new czlowiek(nick2, 'X');
							break;
						}
						//WYJSCIE
						case '0': {
							cout << "\n\nKoniec programu.\n\n";
							return 0;
						}
						default: {
							cout << "\nWybierz z dostepnych opcji!\n";
							decyzja_2 = false; //powrot do menu
						}
					}
				} while (!decyzja_2);
				break;
			}
			//WCZYTYWANIE ZAPISANEJ GRY
			case 'w': {
				ifstream we("zapis.txt");	//plik z zapisem gry
				if (!we) {
					cout << "\nBlad wczytywania zapisu!\n";
					decyzja_1 = false;		//powrot do menu
					break;
				}

				G1=wczytywanie(we ,plansza_gomoku);	//wczytywanie informacji o pierwszym graczu
				G2=wczytywanie(we, plansza_gomoku);	//wczytywanie informacji o drugim graczu
				break;
			}

			//STATYSTYKI
			case 's': {
				string stat;
				ifstream stat_we("statystyki.txt"); //plik zawierajacy statystyki
				if (!stat_we) {
					cout << "\nBlad wczytywania statystyk!\n";
					decyzja_1 = false;		//powrot do menu
					break;
				}

				cout << "\n\tSTATYSTYKI\n" << endl;
				while (!stat_we.eof()) {
					getline(stat_we, stat);  //wczytywanie z pliku
					cout << stat << endl;	//wypisywanie statystyk na ekran
				}
				decyzja_1 = false;   //powrot do menu;
				break;
			}
			
			//WYJSCIE Z GRY
			case '0': {
				cout << "\n\nKoniec programu.\n\n";
				system("PAUSE");
				return 0;
			}
			default: {
				cout << "\nWybierz z dostepnych opcji: \n";
				decyzja_1 = false; //powrot do menu
			}
		}
		while (getchar() != '\n') //czyszczenie bufora 
			;

	} while (!decyzja_1);

	cout << "\n" << G1->get_name() << " Twoje pionki to: " << G1->get_pionek();
	cout << "\n" << G2->get_name() << " Twoje pionki to: " << G2->get_pionek() << endl << endl;

	cout << "\nW kazdej chwili mozesz przerwac gre podajac '0' jako wiersz\n";

	plansza_gomoku.wypisz();  //przedstawienie wygladu planszy

	//ROZGRYWKA
	int koniec = 0;

	//kontrola licznikow ruchow
	//jesli wartosc bezwzgledna miedzy liczba ruchow jest wieksza od 1 to ktos namieszal w pliku i rozgrywka nie powinna sie zaczac
	//wynikaloby z tego ze kotrys gracz mial podwojny ruch

	if ((abs((G1->get_licznik_ruchow()) - (G2->get_licznik_ruchow())))>1) { 
		cout << "\nBlad danych\n" << endl;
		koniec = 3;
	}

	while (koniec == 0) {
		int wyjdz;

		if ((G1->get_licznik_ruchow()) <= (G2->get_licznik_ruchow())) {  //sprawdzanie ktory gracz ostatnio sie ruszal (wazne przy wczytywaniu gry)

			cout << "\nTeraz ruch ma:  " << G1->get_name() << endl; 
			wyjdz = G1->ruch(plansza_gomoku); //w przypadku	checi zakonczenia gry przez uzytkownika, metoda 'ruch' zwraca 0
			if (wyjdz == 0) {
				ofstream wy("zapis.txt");
				zapisywanie(wy, G1);
				zapisywanie(wy, G2);
				cout << "\nGre zapisano!\n" << endl;
				delete G1;
				delete G2;
				cout << "\n\nKoniec programu.\n\n";
				system("PAUSE");
				return 0;
			}

			//metoda 'czy_wygrana' zwraca 1 w przypadku zwyciestwa, 2 w przypadku remisu lub zero w przeciwnym wypadku
			koniec = plansza_gomoku.czy_wygrana(G1);
			if (koniec!=0) {
				if(koniec==1)
					zwyciestwo(G1, G2);
				if (koniec == 2)
					remis(G1, G2);
				delete G1;
				delete G2;
				cout << "\n\nKoniec programu.\n\n";
				system("PAUSE");
				return 0;
			}
		}

		cout << "\nTeraz ruch ma:  " << G2->get_name() << endl;
		wyjdz = G2->ruch(plansza_gomoku);	//w przypadku checi zakonczenia gry przez uzytkownika, metoda 'ruch' zwraca 0

		if(wyjdz==0){
			ofstream wy("zapis.txt");
			zapisywanie(wy, G1);
			zapisywanie(wy, G2);
			cout << "\nGre zapisano!\n" << endl;
			delete G1;
			delete G2;
			cout << "\n\nKoniec programu.\n\n";
			system("PAUSE");
			return 0;
		}

		//metoda 'czy_wygrana' zwraca 1 w przypadku zwyciestwa, 2 w przypadku remisu lub zero w przeciwnym wypadku
		koniec = plansza_gomoku.czy_wygrana(G2); 
		if (koniec!=0) {
			if(koniec==1)
				zwyciestwo(G2, G1);
			if(koniec == 2)
				remis(G2, G1);
			delete G1;
			delete G2;
			cout << "\n\nKoniec programu.\n\n";
			system("PAUSE");
			return 0;
		}
	}

	delete G1;
	delete G2;
	cout << "\n\nKoniec programu.\n\n";
	system("PAUSE");
	return 0;
}

