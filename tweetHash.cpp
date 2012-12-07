#include <cstdlib>
#include <string>
#include <map>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cctype>
#include <unordered_map>
#include <vector>
#include <ctime>

using std::vector;
using std::unordered_map;
using std::unordered_multimap;
using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

int main(int argc, char** argv) {

  if (argc != 2)
    cout << "Usage: list [filename]" << endl;
  else {


    int start = clock();
    char* filename = argv[1];
    ifstream inputFile1(filename);
    string name = "";
    const char* cleansedFileName = "cleantweets";
    ofstream cleansedFile(cleansedFileName);
    char ch;

    const char* outputFileName = "tweets.log";

    // clean the tweets file

    if (inputFile1.is_open() && cleansedFile.is_open()) {
      while (inputFile1.good()) {  
        ch = inputFile1.get();
        if (isspace(ch))
          cleansedFile << endl;
        while (!isalpha(ch) && inputFile1.good()) {
          ch = inputFile1.get();
        }
        if (isalpha(ch)) {
          cleansedFile << (char) tolower(ch);
        }
      }
    }

    inputFile1.close();
    cleansedFile.close();

    long wordCount = 0;
    long distinctWordCount = 0;

    // now open the cleansed file as an input file
    ifstream inputFile(cleansedFileName);

    // this map will hold a name and a count of how many times this name appears in an input file
    unordered_map<string,int> tweetMap;

    // return type from insert into map that returns iterator and boolean
    pair<unordered_map<string,int>::iterator,bool> retPair;

    if (inputFile.is_open()) {
      while (getline(inputFile,name)) {
        retPair = tweetMap.insert(pair<string,int>(name,1));
        wordCount++;

        // if the key is already in the map, the associated value is incremented by 1
        if (retPair.second == false)
          retPair.first->second++;
      }
    }
    inputFile.close();
    distinctWordCount = (long) tweetMap.size();

    // an iterator to the tweetMap map
    unordered_map<string,int>::iterator it;

    // this multimap's key will be the number of times a name appeared in the input file
    // its value will be the name
    // this will allow for a sorted print
    unordered_multimap<int,string> rankedTweets;

    for (it=tweetMap.begin(); it!=tweetMap.end(); it++) {
      rankedTweets.insert(pair<int,string>(it->second,it->first));
    }

    // iterator of ranked unordered_multimap (iterator as reverse iterator not supported)
    unordered_multimap<int,string>::iterator rankIt = rankedTweets.begin(); 

    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {

    outputFile << "Summary Data for 10,000 Tweets" << endl << endl;
    outputFile << "Number of unique words: " << distinctWordCount << endl;
    outputFile << "Total number of words: " << wordCount << endl;
    outputFile << "Lexical Diversity (Total number of words / Number of unique words): ";
    outputFile << (float) wordCount/distinctWordCount << endl << endl << endl;

      outputFile << "Here is a list of each unique word and the number of times it appears:" << endl;
      outputFile << endl;
      
      vector<pair<int,string> > tweetVec;

      // copy the unordered_multimap to a vector in order to write to file in reverse order
      for ( ; rankIt!=rankedTweets.end(); rankIt++) {
        // outputFile << rankIt->second << " " << rankIt->first << endl;
        tweetVec.push_back(pair<int,string>(rankIt->first,rankIt->second));
      } 

      // print out the vector in reverse order   
      vector<pair<int,string> >::reverse_iterator vRit = tweetVec.rbegin();
      for ( ; vRit!=tweetVec.rend(); vRit++) {
        outputFile << vRit->second << " " << vRit->first << endl;
      }

    }

    outputFile.close();
    
    int end = clock();
    int elapsed = end - start;
    cout << (double) elapsed/CLOCKS_PER_SEC << endl;  

  }

  return 0;
}
