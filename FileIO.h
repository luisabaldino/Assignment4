#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class FileIO{
public:
  //Instance variables
  ifstream inFile;
  ofstream outFile;
  string line;

  int lineNbr = 1;
  string *inputArray;

  FileIO(string input); //Constructor
  ~FileIO(); //Destructor

  void createArray(); //Creates array of input info
};

FileIO::FileIO(string input){
  inFile.open(input);
  if (!inFile){
    cout << "Was not able to open file. Please try again." << endl;
  }
}

void FileIO::createArray(){
  //For every line in file, add 1 to lineNbr
  getline(inFile,line);
  while (!inFile.eof()){
    lineNbr += 1;
    getline(inFile,line);
  }
  inFile.seekg(0);
  inputArray = new string[lineNbr];
  //For every line in file, add line to array
  for (int i = 0; i < lineNbr; i++){
    getline(inFile,inputArray[i]);
  }
  inFile.close();
}
