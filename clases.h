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
	string type;
	int years;
	int periods_per_year;
	int num_courses;
	int num_curricula;
	int min_load;
	int max_load;
	int min_amount;
	int max_amount;
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
		min_amount = 0;
		max_amount = 0;
		num_precedences = 0;
		num_undesired_periods = 0;
		courses.clear();
	}
	Instance(string instance_type, int y, int ppy, int ncour, int ncurr, int minl, int maxl, int mina, int maxa, int nprec, int nund, vector<Course> courseVector){
		type = instance_type;
		years = y;
		periods_per_year = ppy;
		num_courses = ncour;
		num_curricula = ncurr;
		min_load = minl;
		max_load = maxl;
		min_amount = mina;
		max_amount = maxa;
		num_precedences = nprec;
		num_undesired_periods = nund;
		courses = courseVector;
	}
	void addCourse(Course c){
		courses.push_back(c);
	}
};


class Period{
public:
	int numero;
	vector <Course> courses;
	Period(){
		numero = 0;
		courses.clear();
	}
	int amount(){
		return courses.size();
	}
	int load(){
		int credits_sum=0;
		for(int i=0; i<courses.size(); i++){
			credits_sum+=courses[i].credits;
		}
		return credits_sum;
	}
	void addCourse(Course c){
		courses.push_back(c);
	}
	void clear(){
		courses.clear();
	}
};

class Solution{
public:
	vector <Period> periods;
	Solution(){
		periods.clear();
	}
	void addPeriod(Period p){
		periods.push_back(p);
	}
};
/*
class Curricula{
public:
	vector <Period> periodos;
};*/