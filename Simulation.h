#include <iostream>
using namespace std;
#include "FileIO.h"
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"

class Simulation{
public:
  //Instance Variables
  FileIO *file;
  string *array;
  int arrayLength;
  int numWindows;
  int nextTime = 1;
  GenQueue<Student> *queue;
  Window *windowArray;
  bool endQueue = false;
  bool allEmptyWindows = true;
  GenLinkedList<Student> *studentList;

  //Constructor/Destructor
  Simulation(string input);
  ~Simulation();

  //Functions
  void runSimulation(); //Runs simulation
  void enqueue(int currTick); //Adds student to queue
};

Simulation::Simulation(string input){
  file = new FileIO(input);
  file->createArray();
  array = file->inputArray;
  arrayLength = file->lineNbr;
  queue = new GenQueue<Student>();
  studentList = new GenLinkedList<Student>();
}
Simulation::~Simulation(){
  file = NULL;
  array = NULL;
  arrayLength = 0;
  numWindows = 0;
  nextTime = 0;
  queue = NULL;
  windowArray = NULL;
  endQueue = false;
  allEmptyWindows = true;
  studentList = NULL;
}
void Simulation::runSimulation(){
  numWindows = std::stoi(array[0]);
  Window *windowArray[numWindows];
  for (int i = 0; i<=numWindows; i++){
    windowArray[i] = new Window();
  }
  int tick = 1;
  while (!allEmptyWindows || !endQueue){
    //enqueue
    enqueue(tick);
      //for each Window
      allEmptyWindows = true;
      for (int i = 1; i<=numWindows; i++){
        //process tick for each window
        windowArray[i]->processTick(tick);
        //if window is free & there are students in the queue
        if (windowArray[i]->isWindowEmpty() && !queue->isEmpty()){
          //Dequeue student and send to window
          Student *currStudent = queue->remove();
          windowArray[i]->acceptStudent(currStudent);
          currStudent->setServiceStatus("inService");
        }
        // When the queue ends, we need to wait untill all windows finish servicing their Students
        // So we`ll only stop when all windows are empty...
        if (!windowArray[i]->isWindowEmpty()){
          allEmptyWindows = false;
        }
      }
      // Students also need to process the tick, to keep track of their time
      if (!studentList->isEmpty()){
        for (int i = 0; i < studentList->getSize(); i++){
          studentList->getElement(i)->processTick(tick);
        }
      }
      tick ++;
  }
  //Calculate stats
  double numStudents = studentList->getSize();
  double totalWait = 0;
  double meanWait = 0;
  int medianWait = 0;
  int longestWait = 0;
  int numWaitingTen = 0;
  double totalIdle = 0;
  double meanIdle = 0;
  int longestIdle = 0;
  int numIdleFive = 0;
  // Get stat data from each student
  for (int i = 0; i < numStudents; i++){
    double w = studentList->getElement(i)->waitingTime;
    totalWait += w;
    if (w > longestWait) longestWait = w;
    if (w > 10) numWaitingTen ++;
    if (i == numStudents/2) meanWait = w;
  }
  // Get stat data from each window
  for (int i = 1; i<=numWindows; i++){
    double idleT = windowArray[i]->idleTime;
    totalIdle += idleT;
    if (idleT>longestIdle) longestIdle = idleT;
    if (idleT > 5) numIdleFive ++;
  }
  // Calc means
  meanWait = totalWait/numStudents;
  meanIdle = totalIdle/(double)numWindows;
  //Print stats
  cout << "Student waiting time mean: " << meanWait << endl;
  cout << "Student waiting time median: " << medianWait << endl;
  cout << "Longest student waiting time: " << longestWait << endl;
  cout << "Number of students who waited longer than 10 ticks: " << numWaitingTen << endl;
  cout << "Window idle time mean: " << meanIdle << endl;
  cout << "Longest window idle time: " << longestIdle << endl;
  cout << "Number of windows that were idle for longer than 5 ticks: " << numIdleFive << endl;

}

// On each tick, takes all arriving students from input array and put them in the queue
void Simulation::enqueue(int currTick){
  if(!endQueue && std::stoi(array[nextTime]) == currTick){
    int timeOfArrival = std::stoi(array[nextTime]);
    int nbrStudents = std::stoi(array[nextTime+1]);
    // Now loop over the service time for the students in this timeslot
    int i;
    for (i = nextTime+2; i <= nextTime+1+nbrStudents; i++){
      // Instantiate the student
      int serviceTime = std::stoi(array[i]);
      Student *student = new Student(i, timeOfArrival, serviceTime);
      // Add student to queue
      queue->insert(student);
      studentList->insertBack(student);
    }
    // Leave the array index ready for use in the next tick
    nextTime = i;
    // If the next index is outside the array, there is no more data to add to queue
    if (nextTime >= arrayLength) endQueue = true;
  }
}
