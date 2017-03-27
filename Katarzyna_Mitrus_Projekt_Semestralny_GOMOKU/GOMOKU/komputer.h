#pragma once

#include "gracz.h"

class komputer :public gracz {
public:
	//konstruktor domyslny / z argumentami
	komputer(string name_kk = "KOMPUTER", char pionek_kk = 'X') :gracz(name_kk, pionek_kk) {};

	int losuj() { return (rand() % 16) + 1; }; //metoda losujaca wspolrzedne
	int ruch(plansza &P1); //metoda sterujaca ruchem komputera
};
