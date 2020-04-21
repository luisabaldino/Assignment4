#pragma once
#include <iostream>
using namespace std;

class Student{
public:
  //Instance Variables
  int timeOfArrival;
  int serviceTime;
  int waitingTime = 0;
  int id;
  string serviceStatus = "inLine";

  //Constructor/destructor
  Student();
  Student(int id, int timeOfArrival, int serviceTime);
  ~Student();

  void processTick(int tick);
  void setServiceStatus(string status);
};
Student::Student(){
  //Nothing (for this assignment)
}
Student::Student(int id, int timeOfArrival, int serviceTime){
  this->timeOfArrival = timeOfArrival;
  this->serviceTime = serviceTime;
  this->id = id;
}
Student::~Student(){
  timeOfArrival = 0;
  serviceTime = 0;
  waitingTime = 0;
  id = 0;
  serviceStatus = "inLine";
}
// Handles everything that the student needs to do at each tick
// Specifically, keeps track of time waiting in line
void Student::processTick(int tick){
  if (serviceStatus == "inLine") {
    waitingTime++;
  }
}
// Sets student statys to either "inLine" (the default), "InService"
void Student::setServiceStatus(string status){
  serviceStatus = status;
}
