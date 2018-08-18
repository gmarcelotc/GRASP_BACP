#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;



vector <vector <string> > loadData(string filename){
	vector <vector <string> > data;
	vector <string> info, courses, curricula, precedence;


	//ifstream instanceTxt("instances/"+filename+".txt");
	ifstream instanceTxt("instances/csplib8.txt");
	if(instanceTxt.fail()){
        cout << "The file does not exist. Please put the file at the instances folder" << endl;
        return data;
    }

	//Extract basic info of the instance
    string wordsToFind[7] = {"YEARS","PERIODS_PER_YEAR","NUM_COURSES","NUM_CURRICULA",
	"MIN_MAX_COURSE_LOAD_PER_PERIOD","NUM_PRECEDENCES","NUM_UNDESIRED_PERIODS"};
	string line =  "";
    while(!instanceTxt.eof()){
    	getline(instanceTxt, line);
    	for(int i=0; i<7; i++){
    		if(line.find(wordsToFind[i]) != string::npos){
    			info.push_back(line+"\n");
    		}
    	}
    }
    instanceTxt.close();
    /*for(int i=0; i<data.size();i++){ 
        cout << data[i];
    }*/

    



    data.push_back(info);
    return data;
}


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