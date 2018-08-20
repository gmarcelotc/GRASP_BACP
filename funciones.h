#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <map>

using namespace std;


const std::string emptyString = "";
std::string ExtractString( std::string source, std::string start, std::string end )
{
     std::size_t startIndex = source.find( start );
     if( startIndex == std::string::npos )
     {
        return emptyString;
     }
     startIndex += start.length();
     std::string::size_type endIndex = source.find( end, startIndex );
     return source.substr( startIndex, endIndex - startIndex );
}

vector <vector <string> > loadData(string filename){
	vector <vector <string> > data;
	vector <string> info, courses, curricula, precedences;
	static const string arr[] = {"YEARS","PERIODS_PER_YEAR","NUM_COURSES","NUM_CURRICULA",
	"MIN_MAX_COURSE_LOAD_PER_PERIOD","MIN_MAX_AMOUNT_COURSES_PER_PERIOD","NUM_PRECEDENCES","NUM_UNDESIRED_PERIODS", "COURSES:","Curr", "PRECEDENCES:"};
	vector <string> wordsToFind (arr, arr + sizeof(arr) /sizeof(arr[0]));
	string line =  "";
	int num_courses, num_precedences, num_curricula;
	bool courses_flag = false;
	bool precedences_flag = false;
	bool curricula_flag = false;
	ifstream instanceTxt("instances/"+filename+".txt");
	//ifstream instanceTxt("instances/csplib8.txt");
	if(instanceTxt.fail()){
        cout << "The file does not exist. Please put the file at the instances folder" << endl;
        return data;
    }
    while(!instanceTxt.eof()){
    	getline(instanceTxt, line);
    	if(courses_flag != true && precedences_flag != true && curricula_flag != true){
    		for(int i=0; i<wordsToFind.size(); i++){
	    		if(line.find(wordsToFind[i]) != string::npos){
	    			if(wordsToFind[i]=="NUM_COURSES"){
	    				string temp = line;
	    				string temp2 = ExtractString(temp,"NUM_COURSES: ","\n");
	    				num_courses = std::stoi(temp2);
	    			}
	    			if(wordsToFind[i]=="NUM_CURRICULA"){
	    				string temp = line;
	    				string temp2 = ExtractString(temp,"NUM_CURRICULA: ","\n");
	    				num_curricula = std::stoi(temp2);
	    			}
	    			if(wordsToFind[i]=="NUM_PRECEDENCES"){
	    				string temp = line;
	    				string temp2 = ExtractString(temp,"NUM_PRECEDENCES: ","\n");
	    				num_precedences = std::stoi(temp2);
	    			}
	    			//cout << wordsToFind[i];
	    			if(wordsToFind[i]=="COURSES:"){
	    				courses_flag = true;
	    				break;
	    			}
	    			if(wordsToFind[i]=="Curr"){
	    				curricula.push_back(line);
	    				num_curricula--;
	    				if(num_curricula>0){
	    					curricula_flag = true;
	    				}
	    				break;
	    			}
	    			if(wordsToFind[i]=="PRECEDENCES:"){
	    				precedences_flag = true;
	    				break;
	    			}
	    			info.push_back(line+"\n");
	    			wordsToFind.erase(wordsToFind.begin());
	    			break;
	    		}
	    	}
	    	continue;
    	}
    	else if(courses_flag == true && num_courses > 0){
    		//cout << "PASO POR ACA 5\n";
    		courses.push_back("&"+line+"\n");
    		num_courses--;
    		if(num_courses == 0){
    			courses_flag = false;
    			wordsToFind.erase(wordsToFind.begin());
    		}
    		continue;
    	}
    	else if(curricula_flag == true && num_curricula > 0){
    		//cout << "PASO POR ACA 5\n";
    		curricula.push_back("&"+line+"\n");
    		num_curricula--;
    		if(num_curricula == 0){
    			curricula_flag = false;
    			wordsToFind.erase(wordsToFind.begin());
    		}
    		continue;
    	}
    	else if(precedences_flag == true && num_precedences > 0){
    		precedences.push_back("&"+line+"\n");
    		num_precedences--;
    		if(num_precedences == 0){
    			precedences_flag = false;
    			wordsToFind.erase(wordsToFind.begin());
    		}
    		continue;
    	}
    }
    instanceTxt.close();
    /*for(int i=0; i<info.size();i++){ 
        cout << info[i];
    }
    for(int i=0; i<courses.size();i++){ 
        cout << courses[i] <<"\n";
    }
    for(int i=0; i<curricula.size();i++){ 
        cout << curricula[i] <<"\n";
    }
    for(int i=0; i<precedences.size();i++){ 
        cout << precedences[i] <<"\n";
    }*/
    data.push_back(info);
    data.push_back(courses);
    data.push_back(curricula);
    data.push_back(precedences);

    cout << "Reading data from instance.txt" << endl;

    return data;
}


vector <Course> processCourses(vector < vector <string> > data){
	vector <Course> coursesVector; 
	vector <string> courses, precedences;
	//map <string, string> linked_precedences;
	vector < vector <string> > linked_precedences;
	courses = data[1];
	precedences = data[3];
	for (int j=0; j<precedences.size(); j++){
		vector <string> temp_vector;
		string course_name = ExtractString(precedences[j],"&"," ");
		temp_vector.push_back(course_name);
		string precedence_name = ExtractString(precedences[j]," ","\n");
		temp_vector.push_back(precedence_name);
		linked_precedences.push_back(temp_vector);
		//linked_precedences[course_name] = precedence_name;
	}
	for(int i=0; i<courses.size(); i++){
		string name = ExtractString(courses[i],"&"," ");
		string tmp1 = ExtractString(courses[i]," ","\n");
		vector <string> temp_precedences;
		int credits = std::stoi(tmp1);
		for(int k=0; k<linked_precedences.size(); k++){
			if(linked_precedences[k][0]== name){
				temp_precedences.push_back(linked_precedences[k][1]);
			}
		}
		/*map<string, string>::iterator iter;
		for(iter = linked_precedences.begin(); iter!=linked_precedences.end(); iter++){
			if(iter->first == name){
				temp_precedences.push_back(iter->second);
			}
		}*/
		Course temp_course(name, credits, temp_precedences);
		coursesVector.push_back(temp_course);
	}
	cout << "Procesing courses from read data" << endl;

	return coursesVector;
}


Instance createInstance(vector <vector <string> > data, vector < Course> courses, string instance_type){
	vector <string> info = data[0];
	string years = ExtractString(info[0],"YEARS: ","\n");
	string ppy = ExtractString(info[1],"PERIODS_PER_YEAR: ","\n");
	string n_cour = ExtractString(info[2],"NUM_COURSES: ","\n");
	string n_curri = ExtractString(info[3],"NUM_CURRICULA: ","\n");
	string prec = ExtractString(info[info.size()-2],"NUM_PRECEDENCES: ","\n");
	string n_und = ExtractString(info[info.size()-1],"NUM_UNDESIRED_PERIODS: ","\n");
	int years2 = std::stoi(years);
	int ppy2 = std::stoi(ppy);
	int n_cour2 = std::stoi(n_cour);
	int n_curri2 = std::stoi(n_curri);
	int prec2 = std::stoi(prec);
	int n_und2 = std::stoi(n_und);

	cout << "Creating instance class with all the data" << endl;
	
	if(instance_type == "csplib"){
		string min_load = ExtractString(info[4],"MIN_MAX_COURSE_LOAD_PER_PERIOD: "," ");
		string max_load = ExtractString(info[4],min_load+" ","\n");
		string min_amount = ExtractString(info[5],"MIN_MAX_AMOUNT_COURSES_PER_PERIOD: "," ");
		string max_amount = ExtractString(info[5],min_amount+" ","\n");
		int minl = std::stoi(min_load);
		int maxl = std::stoi(max_load);
		int mina = std::stoi(min_amount);
		int maxa = std::stoi(max_amount);
		Instance bacpInstance(instance_type, years2, ppy2, n_cour2, n_curri2, minl, maxl, mina, maxa, prec2, n_und2, courses);
		return bacpInstance;
	}	
	else if(instance_type == "UD"){
		string min_load = ExtractString(info[4],"MIN_MAX_COURSE_LOAD_PER_PERIOD: "," ");
		string max_load = ExtractString(info[4],min_load+" ","\n");
		int minl = std::stoi(min_load);
		int maxl = std::stoi(max_load);
		Instance bacpInstance(instance_type, years2, ppy2, n_cour2, n_curri2, 0, 0, minl, maxl, prec2, n_und2, courses);
		return bacpInstance;
	}
	else{
		Instance bacpInstance;
		return bacpInstance;
	}
	
}

int randomNumber(int a,int b){
    unsigned seed = unsigned (chrono::system_clock::now().time_since_epoch().count());
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(a,b);
    int dice_roll = distribution(generator);
    return dice_roll;
}

bool precedencesRestriction(Solution actual_solution, Course actual_course){
	//cout << "Entro en funcion de pre-requisitos" << endl;
	bool complies_with_precedence = false;
	if(actual_course.precedences.size() == 0){
		//cout << "Primer if de Pre-requisitos" << endl;
		return true;
	}
	else{
		for(int p=0; p<actual_course.precedences.size(); p++){
			//cout << "Primer FOR de Pre-requisitos" << endl;
			if(complies_with_precedence == true){
				break;
			}
			for(int i=0; i<actual_solution.periods.size(); i++){
				//cout << "Segundo FOR de Pre-requisitos" << endl;
				if(complies_with_precedence == true){
					break;
				}
				for(int j=0; j<actual_solution.periods[i].courses.size(); j++){
					//cout << "Tercer FOR de Pre-requisitos" << endl;
					if(actual_course.precedences[p] == actual_solution.periods[i].courses[j].name){
						complies_with_precedence = true;
						break;
					}
				}
			}
		}
	}
	return complies_with_precedence;
}

int miopeFunction(vector <Course> courses, Instance bacpInstance, Solution actual_solution ,Period current_period){
	int alpha = randomNumber(0,6);
	int beta = randomNumber(0,4);
	for(int i=0; i<courses.size();i++){
		if(current_period.load() + courses[i].credits <= bacpInstance.max_load - alpha &&
			current_period.amount() + 1 <= bacpInstance.max_amount - beta){
			//cout << "Entro en if de restricciones basicas" << endl;
			if(precedencesRestriction(actual_solution, courses[i])){
				return i;
			}
		}
		//cout << "This course not meet restrictions" << endl;
	}
	return -1;
}


Solution graspBuildSolution(Instance bacpInstance, int l){

	cout << "Begin to building solution" << endl;
	int number_periods = bacpInstance.years*bacpInstance.periods_per_year;
	vector <Course> courses = bacpInstance.courses;
	Solution actual_solution;
	Period current_period;
	current_period.addCourse(courses[0]);
	courses.erase(courses.begin());
	bool error_flag = true;
	while(courses.size()>0 && number_periods > 0 && error_flag){
		vector <Course> courses_copy = courses;
		vector <Course> LRC;
		vector <int> index_for_LRC; 
		while(LRC.size()<l){
			//cout << "Entro while LRC" << endl;
			int miopeValue = miopeFunction(courses_copy, bacpInstance, actual_solution, current_period);
			//cout << "valor funcion miope: "<< miopeValue << endl;
			if(miopeValue != -1){
				//cout << "Saving into LRC" << endl;
				LRC.push_back(courses_copy[miopeValue]);
				index_for_LRC.push_back(miopeValue);
				courses_copy.erase(courses_copy.begin()+miopeValue);
			}
			else if(current_period.load() >= bacpInstance.min_load &&
					current_period.amount() >= bacpInstance.min_amount){
				cout << "Saving period " << 9 -number_periods<< " to solution (" <<
				current_period.amount() << " courses, "<<current_period.load() << " credits)" <<  endl;
				actual_solution.addPeriod(current_period);
				number_periods--;
				current_period.clear();
				break;
			}
			else{
				//cout << "Error: Miss courses/Miss periods" << endl;
				//error_flag = false;
				break;
			}
		}
		//cout << "LRC size: " << LRC.size()<< endl;
		if(LRC.size()>1){
			int random_index = randomNumber(1,LRC.size());
			current_period.addCourse(LRC[random_index-1]);
			cout << "Saving " << LRC[random_index-1].name <<" to period" << endl;
			//courses.erase(courses.begin()+index_for_LRC[random_index-1]);
			for(int j=0; j<courses.size();j++){
				if(courses[j].name == LRC[random_index-1].name){
					courses.erase(courses.begin()+j);
					continue;
				}
			}
		}
		else if(LRC.size() == 1){
			current_period.addCourse(LRC[0]);
			cout << "Saving 2 " << LRC[0].name <<" to period" << endl;
			//courses.erase(courses.begin()+index_for_LRC[0]);
			for(int j=0; j<courses.size();j++){
				if(courses[j].name == LRC[0].name){
					courses.erase(courses.begin()+j);
					continue;
				}
			}
		}
		
		/*if(current_period.load >= bacpInstance.min_load &&
			current_period.amount >= bacpInstance.min_amount){

		}*/
	}
	return actual_solution;
}










/*
void processData(vector < vector <string> > data){
	vector <string> info, courses, curricula, precedences;
	info = data[0];
	courses = data[1];
	curricula = data[2];
	precedences = data[3];

}*/