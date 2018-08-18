#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

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
	    				curricula_flag = true;
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
    		courses.push_back(line);
    		num_courses--;
    		if(num_courses == 0){
    			courses_flag = false;
    			wordsToFind.erase(wordsToFind.begin());
    		}
    		continue;
    	}
    	else if(curricula_flag == true && num_curricula > 0){
    		//cout << "PASO POR ACA 5\n";
    		curricula.push_back(line);
    		num_curricula--;
    		if(num_curricula == 0){
    			curricula_flag = false;
    			wordsToFind.erase(wordsToFind.begin());
    		}
    		continue;
    	}
    	else if(precedences_flag == true && num_precedences > 0){
    		precedences.push_back(line);
    		num_precedences--;
    		if(num_precedences == 0){
    			precedences_flag = false;
    			wordsToFind.erase(wordsToFind.begin());
    		}
    		continue;
    	}
    	
    }
    instanceTxt.close();
    for(int i=0; i<info.size();i++){ 
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
    }

    //Extract the courses of the instance


    //Extract the curricula of the instance
    //Extract the procedences of the instance



    data.push_back(info);
    return data;
}




void processData(Instance instance){

}







    /*
    string firewallLogString = "";
    ifstream firewallLog("instances/csplib8.gbac.txt");
    ofstream condensedFirewallLog("instances/adsasdsa.txt");
    if(firewallLog.fail())
    {
        cout << "The file does not exist. Please put the file at the instances folder" << endl;
        system("PAUSE");
        return 0;
    }
    vector<string>  data;
    bool curricula = false;
    while(!firewallLog.eof())
    {
        getline(firewallLog, firewallLogString);

        if(curricula == true){
        		data.push_back("CURRICULA:"+firewallLogString);
            	//cout << firewallLogString;
            	curricula = false;
            }

            for(int i = 0; i < 7; i++)
            {
                if(firewallLogString.find(wordsToFind[i]) != string::npos)
                {
                	data.push_back(firewallLogString);
                }
                else if (firewallLogString.find("CURRICULA") != string::npos){
                	curricula = true;
                }
            }
            
    }
    condensedFirewallLog.close();
    firewallLog.close();

    for(int i=1; i<data.size();i++){ 
        cout << data[i] << "\n";
    }*/