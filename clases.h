#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
 

using namespace std;


class Course{
public:
	string name;
	int	credits;
	vector <string> precedences;
	Course(){
		name = "";
		credits = 0;
		precedences.clear();
	}
	Course(string n, int c, vector <string> p){
		name = n;
		credits = c;
		precedences = p;
	}
	void addPrecedende(string p){
		precedences.push_back(p);
	}
};

class Instance{
public:
	int years;
	int periods_per_year;
	int num_courses;
	int num_curricula;
	int min_load;
	int max_load;
	int num_precedences;
	int num_undesired_periods;
	vector <Course> courses;
	Instance(){
		years =0;
		periods_per_year =0;
		num_courses = 0;
		num_curricula = 0;
		min_load = 0;
		max_load = 0;
		num_precedences = 0;
		num_undesired_periods = 0;
		courses.clear();
	}
	Instance(int y, int ppy, int ncour, int ncurr, int min, int max, int nprec, int nund){
		years = y;
		periods_per_year = ppy;
		num_courses = ncour;
		num_curricula = ncurr;
		min_load = min;
		max_load = max;
		num_precedences = nprec;
		num_undesired_periods = nund;
	}
	void addCourse(Course c){
		courses.push_back(c);
	}
};


class Period{
public:
	int numero;
	vector <Course> cursos;
};

class Curricula{
public:
	vector <Period> periodos;
};