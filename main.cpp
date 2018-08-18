#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
#include <algorithm>


using namespace std;



#include "clases.h"
#include "funciones.h"

int main() {

	string instance;
	string seed;
    cout << "Insert instance name (Ex:csplib8, UD1): ";
    cin >> instance;
    cout << "Insert seed (Ex: 1, 2): ";
    cin >> seed;

    vector < vector <string> > data = loadData(instance);
    cout << data[0][0];

	/*
    vector <string> data =loadData(instance);

    //processData(data);
    string num1 =  ExtractString(data[0],"YEARS: ","\n");
    int num2 = std::stoi(num1);
    cout << 3 + num2 << "\n";
    //cout << data[0];

    Instance asd1;
    cout << asd1.years << "\n";

    vector <string> requisitos;
    requisitos.push_back("ili123");
    requisitos.push_back("inf245");

    Course curso1("cc1", 4, requisitos);

    asd1.addCourse(curso1);

    cout << asd1.courses[0].precedences[0];

    */

    //unsigned asd = data[0].find("YEARS:");
    //cout << asd;



/*



*/


    //GRASP --- 3 steps ---


    // ---- Etapa 1: Pre-porcesamiento

    // ---- Etapa 2: Construir solución

    // ---- Etapa 3: Post-procesamiento
}