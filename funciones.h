#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
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
	"MIN_MAX_COURSE_LOAD_PER_PERIOD","NUM_PRECEDENCES","NUM_UNDESIRED_PERIODS", "COURSES:","Curr", "PRECEDENCES:"};
	vector <string> wordsToFind (arr, arr + sizeof(arr) /sizeof(arr[0]));
	string line =  "";
	int num_courses, num_precedences, num_curricula;
	bool courses_flag = false;
	bool precedences_flag = false;
	bool curricula_flag = false;
	//ifstream instanceTxt("instances/"+filename+".txt");
	ifstream instanceTxt("instances/csplib8.txt");
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
	//cout << coursesVector[10].name <<" " <<  coursesVector[10].credits << " " << coursesVector[10].precedences.size() << "\n";
	return coursesVector;
}


Instance createInstance(vector <vector <string> > data, vector < Course> courses){
	vector <string> info = data[0];
	string years = ExtractString(info[0],"YEARS: ","\n");
	string ppy = ExtractString(info[1],"PERIODS_PER_YEAR: ","\n");
	string n_cour = ExtractString(info[2],"NUM_COURSES: ","\n");
	string n_curri = ExtractString(info[3],"NUM_CURRICULA: ","\n");
	string min = ExtractString(info[4],"MIN_MAX_COURSE_LOAD_PER_PERIOD: "," ");
	string max = ExtractString(info[4],min+" ","\n");
	string prec = ExtractString(info[5],"NUM_PRECEDENCES: ","\n");
	string n_und = ExtractString(info[6],"NUM_UNDESIRED_PERIODS: ","\n");

	int years2 = std::stoi(years);
	int ppy2 = std::stoi(ppy);
	int n_cour2 = std::stoi(n_cour);
	int n_curri2 = std::stoi(n_curri);
	int min2 = std::stoi(min);
	int max2 = std::stoi(max);
	int prec2 = std::stoi(prec);
	int n_und2 = std::stoi(n_und);

	//Instance bacpInstance(years2, ppy2, n_cour2, n_curri2, min2, max2, prec2, n_und2, courses);
	return bacpInstance;
}









/*
void processData(vector < vector <string> > data){
	vector <string> info, courses, curricula, precedences;
	info = data[0];
	courses = data[1];
	curricula = data[2];
	precedences = data[3];

}*/