#include "funkcje.h"
//funkcja do przeskakiwania do odpowiedniej linii
std::ifstream& GotoLine(std::ifstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

//funkcja przyjmuje na wejściu wektor z danym (np nazwy wytworzonych cząsteczek, pędy...)
//a następnie podlicza ile razy wystąpiła każda wartość i umieszcza te dane w wektorze
//docelowo będzie to wektor wektorów, w pierwszej kolumnie znajduje się wartość a w drugiej ilość zliczeń
vector<vector<double>> ilosc_wystapien(vector <double> vec)
{
    int N = vec.size();

    vector<vector<double>> ret;
	
	vector<double> temp;
	
	//ret.resize(N);
	
	//temp.resize(2);

	//podliczanie konkretnych wejść
    int seen[N];
    for(int i = 0; i < N; i++)
        seen[i] = 0;
	
    for(int i = 0; i < N; i++) {
        if(seen[i] == 0) {
            int count = 0;
            for(int j = i; j < N; j++)
                if(vec[j] == vec[i]) {
                    count += 1;
                    seen[j] = 1;
                }
            cout << vec[i] << " occurs " << count << " times" << endl;//cout dla porównania
			temp.push_back(vec[i]);//jaka wielkość
			temp.push_back(count);//ile zliczeń
			//ret.push_back(vec[i]);
			ret.push_back(temp);
			//cout<</*ret.size()*/(ret.at(i)).at(1)<<endl;//próba odwołania się do wielkości w drugim rzędzie i pierwszej kolumnie
			//cout<<temp[1]<<endl;
			temp.clear();//czyszczenie wektora tmp w celu przyjęcia nowych wielkości
        }
    }
	
	//cout<<ret.at(2).at(1)<<endl;

    return ret;
}

vector<vector<double>> wybierz_czastke(vector<vector<double>> vec, int zadane)
{
	vector<double> potrzebne;
	
	vector<vector<double>> dane_szukane;

	for(int i = 0; i<vec.size(); i++)
	{
		if(vec.at(i).at(0)==zadane)
		{
			potrzebne.push_back(vec.at(i).at(0));
			potrzebne.push_back(vec.at(i).at(1));
			dane_szukane.push_back(potrzebne);
			potrzebne.clear();
		}
	}
	
	return dane_szukane;
}

vector<double>  wybierz_dane(vector<double> ID, vector<double> dane, int zadane)
{
	vector<double> dane_szukane;

	for(int i = 0; i<ID.size(); i++)
	{
		if(ID.at(i)==zadane)
		{
			dane_szukane.push_back(dane.at(i));
		}
	}
	
	return dane_szukane;
}


