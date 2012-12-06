#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>

using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

int main(int argc, char** argv) {

  if (argc != 3)
    cout << "Usage: list [filename] [threshold]" << endl;
  assert(argc == 3);

  char* filename = argv[1];
  ifstream inputFile(filename);
  int threshold = atoi(argv[2]);
  string name;

  map<string,int> naughtyNice;
  pair<map<string,int>::iterator,bool> retPair;

  if (inputFile.is_open()) {
    while (inputFile.good()) {
      getline(inputFile,name);
      retPair = naughtyNice.insert(pair<string,int>(name,1));
      if (retPair.second == false)
        retPair.first->second++;
    }
  }
  inputFile.close();

  map<string,int>::iterator it;
  multimap<int,string> rankedNaughtyNice;

  for (it=naughtyNice.begin(); it!=naughtyNice.end(); it++) {
    rankedNaughtyNice.insert(pair<int,string>(it->second,it->first));
  }

  // reverse iterator of ranked multimap
  multimap<int,string>::reverse_iterator rankRevIt = rankedNaughtyNice.rbegin(); 

  ofstream outputFile("NaughtyNiceList.log");
  if (outputFile.is_open()) {
    outputFile << "Naughty / Nice List with threshold = " << threshold << endl << endl;
    if (rankRevIt->first > threshold)
      outputFile << "Nice List:" << endl;
    else
      outputFile << "Nobody on Nice List!" << endl << endl; 
  

    while (rankRevIt->first > threshold && rankRevIt!=rankedNaughtyNice.rend()) {  
      outputFile << rankRevIt->second << " " << rankRevIt->first << endl;
      rankRevIt++;
    }

    outputFile << endl;
    if (rankRevIt->first == threshold)
      outputFile << "Right on the Naughty/Nice threshold:" << endl;
    else
      outputFile << "Nobody right on the Naughty/Nice threshold." << endl << endl; 

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

  return 0;
}