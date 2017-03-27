#include "gracz.h"

//metoda wypisujaca plansze na ekran
void plansza::wypisz() {
	cout << "\n   |a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|" << endl;
	for (int i = 0; i < MAX; i++) {
		cout << "   -------------------------------\n" << setw(3) << right << i + 1 << "|";
		for (int j = 0; j < MAX; j++) {
			cout << pole[i][j] << "|";
		}
		cout << endl;
	}
}

// metoda sprawdzajaca czy dany gracz juz wygral
int plansza::czy_wygrana(gracz *zwyciezca) {
	int licznik;

	//remis
	licznik = 1;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++) {
			if(pole[i][j] == 0)
				licznik=0;
		}
	if (licznik != 0) {
		return 2; //remis
	}

	//poziomo (w wierszach)

	for (int i = 0; i < MAX; i++) {
		licznik = 0;
		for (int j = 0; j < MAX; j++) {
			if (pole[i][j] == zwyciezca->get_pionek())
				licznik++;
			else licznik = 0;
			if (j == (MAX - 1) && licznik == 5) { //jesli to krawedz planszy "overline" nie jest mozliwy
				zwyciezca->set_wygrana(true);
				return 1;
			}
			else if (licznik == gom && pole[i][j + 1] != zwyciezca->get_pionek()) { //sprawdzanie "overline"
				zwyciezca->set_wygrana(true);
				return 1;
			}
		}
	}

	//pionowo (w kolumnach)

	for (int i = 0; i < MAX; i++) {
		licznik = 0;
		for (int j = 0; j < MAX; j++) {
			if (pole[j][i] == zwyciezca->get_pionek())
				licznik++;
			else licznik = 0;
			if (j == (MAX - 1) && licznik == 5) { //jesli to krawedz planszy "overline" nie jest mozliwy
				zwyciezca->set_wygrana(true);
				return 1;
			}
			else if (licznik == gom && pole[j + 1][i] != zwyciezca->get_pionek()) { //sprawdzanie "overline"
				zwyciezca->set_wygrana(true);
				return 1;
			}
		}
	}

	////SKOSY////

	////zakres:
	//// ---/+
	//// --/++
	//// -/+++

	for (int prog = (MAX - 1);prog >= 0;prog--) {
		for (int i = prog, j = (MAX-1);i < MAX;i++, j--) {
			if (pole[i][j] == zwyciezca->get_pionek())
				licznik++;
			else licznik = 0;
			if ((j == 0 && licznik == gom) || (i == (MAX-1) && licznik == gom)) { //jesli to krawedz planszy "overline" nie jest mozliwy
				zwyciezca->set_wygrana(true);
				return 1;
			}
			else if (licznik == gom && pole[i + 1][j - 1] != zwyciezca->get_pionek()) { //sprawdzanie "overline"
				zwyciezca->set_wygrana(true);
				return 1;
			}
		}
	}

	////zakres:
	//// +++/-
	//// ++/--
	//// +/---

	for (int prog = 0;prog < MAX;prog++) {
		for (int i = prog, j = 0;i >= 0;i--, j++) {
			if (pole[i][j] == zwyciezca->get_pionek())
				licznik++;
			else licznik = 0;
			if ((j == (MAX-1) && licznik == gom) || (i == 0 && licznik == gom)) { //jesli to krawedz planszy "overline" nie jest mozliwy
				zwyciezca->set_wygrana(true);
				return 1;
			}
			else if (licznik == gom && pole[i - 1][j + 1] != zwyciezca->get_pionek()) { //sprawdzanie "overline"
				zwyciezca->set_wygrana(true);
				return 1;
			}
		}
	}

	////zakres:
	//// -\+++
	//// --\++
	//// ---\+

	for (int prog = (MAX - 1);prog >= 0;prog--) {
		licznik = 0;
		for (int i = prog, j = 0;i < MAX;i++, j++) {
			if (pole[i][j] == zwyciezca->get_pionek())
				licznik++;
			else licznik = 0;
			if ((j == (MAX - 1) && licznik == 5) || (i == (MAX - 1) && licznik == 5)) { //jesli to krawedz planszy "overline" nie jest mozliwy
				zwyciezca->set_wygrana(true);
				return 1;
			}
			else if (licznik == gom && pole[i + 1][i + 1] != zwyciezca->get_pionek()) { //sprawdzanie "overline"
				zwyciezca->set_wygrana(true);
				return 1;
			}
		}
	}


	////zakres:
	//// +\---
	//// ++\--
	//// +++\-

	for (int prog = (MAX - 1);prog >= 0;prog--) {
		licznik = 0;
		for (int i = prog, j = 0;i < MAX;i++, j++) {
			if (pole[j][i] == zwyciezca->get_pionek())
				licznik++;
			else licznik = 0;
			if ((j == (MAX - 1) && licznik == 5) || (i == (MAX - 1) && licznik == 5)) { //jesli to krawedz planszy "overline" nie jest mozliwy
				zwyciezca->set_wygrana(true);
				return 1;
			}
			else if (licznik == gom && pole[j + 1][i + 1] != zwyciezca->get_pionek()) { //sprawdzanie "overline"
				zwyciezca->set_wygrana(true);
				return 1;
			}
		}
	}

	return 0;
}
