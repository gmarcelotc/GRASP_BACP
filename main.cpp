#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <map>



using namespace std;



#include "clases.h"
#include "funciones.h"

int main() {

	string instance_type;
	string instance_number;
	/*
	cout << "Select instance type:" << "\n"<<"1 - csplib" << "\n"<<"2 - UD" <<"\n";
	cin >> instance_type;
	if(instance_type == "1"){
		cout << "select number of instance (8, 10, or 12): ";
		cin >> instance_number;
		instance_type = "csplib";
	}
	else if(instance_type == "2"){
		cout << "Select number of instance (1,2,3,...,10): ";
    	cin >> instance_number;
    	instance_type = "UD";
	}
	else{
		cout << "Error \n";
	}*/

	instance_type = "csplib";
	instance_number = "8";
    

    vector < vector <string> > data = loadData(instance_type+instance_number);
    vector <Course> courses = processCourses(data);
    Instance bacpInstance = createInstance(data, courses, instance_type);

    Solution first_solution = graspBuildSolution(bacpInstance,3);

    int totalCredits = 0;
    for(int i=0; i<courses.size(); i++){
		totalCredits += courses[i].credits;
	}

	cout << "Creditos totales: " <<totalCredits<< endl;
    /*
    cout << "años: " << bacpInstance.years << "\n" 
    << "periodos por año: " << bacpInstance.periods_per_year << "\n" 
    <<  "numero de cursos: " <<bacpInstance.num_courses << "\n"
     << "minimo de cursos por periodo: "<<bacpInstance.min_amount <<"\n"
     << "maximo de cursos por periodo: "<<bacpInstance.max_amount <<"\n"
     << "minimo de creditos por periodo: "<<bacpInstance.min_load <<"\n"
     << "maximo de creditos por periodo: "<<bacpInstance.max_load <<"\n";
	*/
     

	/*
	vector <int> asd;
	asd.push_back(3);
	asd.push_back(6);
	asd.push_back(9);
	asd.push_back(12);

	for(int i=0; i<asd.size(); i++){
		cout << asd[i] << endl;
	}

	asd.erase(asd.begin()+1);

	cout << "nuevo vector:" << endl;
	for(int i=0; i<asd.size(); i++){
		cout << asd[i] << endl;
	}*/

    //graspBuildSolution(bacpInstance);

    //cout << bacpInstance.years << " " << bacpInstance.num_courses;
    //cout << data[0][0];

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