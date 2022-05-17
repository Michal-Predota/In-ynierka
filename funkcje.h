#ifndef _FUNKCJE_H
#define _FUNKCJE_H

#include <fstream>
#include <limits>

using namespace std;

std::fstream& GotoLine(std::fstream& file, unsigned int num);

vector<vector<double>> ilosc_wystapien(vector <double> vec);

vector<string> odkodowanie(vector<vector<double>> vec);

vector<vector<double>> wybierz_czastke(vector<vector<double>> ID, int zadane);

vector<double>  wybierz_dane(vector<double> ID, vector<double> dane, int zadane);

#endif