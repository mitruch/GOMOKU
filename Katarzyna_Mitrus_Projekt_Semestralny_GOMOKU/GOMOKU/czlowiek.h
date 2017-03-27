#pragma once

#include "gracz.h"

class czlowiek :public gracz {
public:
	//konstruktor domyslny / z argumentami
	czlowiek(string name_kcz = "Czlowiek", char pionek_kcz = 'O') :gracz(name_kcz, pionek_kcz) {};

	int ruch(plansza &P1); 
};
