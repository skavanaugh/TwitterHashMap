#include <cstdlib>
#include <string>
#include <map>
#include <cassert>
#include <fstream>
#include <iostream>

using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

int main(int argc, char** argv) {

  if (argc != 3)
    cout << "Usage: list [filename] [threshold]" << endl;
  else { 

    char* filename = argv[1];
    ifstream inputFile(filename);
    int threshold = atoi(argv[2]);
    string name = "";
    const char* outputFileName = "NaughtyNice.log";

    // this map will hold a name and a count of how many times this name appears in an input file
    map<string,int> naughtyNice;

    // return type from insert into map that returns iterator and boolean
    pair<map<string,int>::iterator,bool> retPair;

    if (inputFile.is_open()) {
      while (getline(inputFile,name)) {
        // getline(inputFile,name);
        retPair = naughtyNice.insert(pair<string,int>(name,1));

        // if the key is already in the map, the associated value is incremented by 1
        if (retPair.second == false)
          retPair.first->second++;
      }
    }
    inputFile.close();

    // an iterator to the naughtyNice map
    map<string,int>::iterator it;

    // this multimap's key will be the number of times a name appeared in the input file
    // its value will be the name
    // this will allow for a sorted print
    multimap<int,string> rankedNaughtyNice;

    for (it=naughtyNice.begin(); it!=naughtyNice.end(); it++) {
      rankedNaughtyNice.insert(pair<int,string>(it->second,it->first));
    }

    // reverse iterator of ranked multimap
    multimap<int,string>::reverse_iterator rankRevIt = rankedNaughtyNice.rbegin(); 

    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {

      outputFile << "Naughty / Nice List with threshold = " << threshold << endl << endl;

      if (rankRevIt->first > threshold)
        outputFile << "Nice List:" << endl;
      else
        outputFile << "Nobody on Nice List!" << endl; 
  
      while (rankRevIt->first > threshold && rankRevIt!=rankedNaughtyNice.rend()) {  
        outputFile << rankRevIt->second << " " << rankRevIt->first << endl;
        rankRevIt++;
      }

      outputFile << endl;
      if (rankRevIt->first == threshold)
        outputFile << "Right on the Naughty/Nice threshold:" << endl;
      else
        outputFile << "Nobody right on the Naughty/Nice threshold." << endl; 

      while (rankRevIt->first == threshold && rankRevIt!=rankedNaughtyNice.rend()) {  
        outputFile << rankRevIt->second << " " << rankRevIt->first << endl;
        rankRevIt++;
      }
    
      outputFile << endl;
      if (rankRevIt->first < threshold)
        outputFile << "Naughty list:" << endl;
      else
        outputFile << "Nobody on the Naughty List!" << endl; 

      while (rankRevIt->first < threshold && rankRevIt!=rankedNaughtyNice.rend()) {  
        outputFile << rankRevIt->second << " " << rankRevIt->first << endl;
        rankRevIt++;
      }
    }

    outputFile.close();
  }
  return 0;
}
