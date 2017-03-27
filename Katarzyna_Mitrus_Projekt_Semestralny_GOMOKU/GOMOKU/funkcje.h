#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

#include "gracz.h"
#include "czlowiek.h"
#include "komputer.h"

using namespace std;

gracz* wczytywanie(ifstream &wczyt, plansza &pln);
void zapisywanie(ofstream &zapisz, gracz *player);


//szablon funkcji zwyciestwo
template <typename T1, typename T2>   
void zwyciestwo(T1* wygrany, T2* przegrany) {

	ofstream stat_wy("statystyki.txt", ios::app);
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	cout << "\n\tZWYCIESTWO !!!" << endl;
	cout << "\tWygrywa " << wygrany->get_name() << endl;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%d.%m.20%y  %H:%M:%S ", timeinfo);
	stat_wy << wygrany->get_name() << " wygrywa z " << przegrany->get_name() << " " << buffer << endl;
}

//szablon funkcji remis
template <typename Tp1, typename Tp2>
void remis(Tp1* wygrany1, Tp2* wygrany2) {

	ofstream stat_wy("statystyki.txt", ios::app);
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	cout << "\n\tREMIS !!!" << endl;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%d.%m.20%y  %H:%M:%S ", timeinfo);
	stat_wy << wygrany1->get_name() << " remisuje z " << wygrany2->get_name() << " " << buffer << endl;
}


