#include <iostream>
#include "Student.h"
using namespace std;

class Window{
public:
  //Instance Variables
  int inServiceTime;
  int idleTime;
  int currStudentTime;
  Student *currStudent;
  bool isEmpty = true;

  //Constructor/Destructor
  Window();
  ~Window();

  //Functions
  bool isWindowEmpty(); //Returns whether window is empty
  void processTick(int tick); //Processes current tick for specific window
  void acceptStudent(Student *student); //Accept new student to window
};
Window::Window(){
  inServiceTime = 0;
  idleTime = 0;
}
Window::~Window(){
  inServiceTime = 0;
  idleTime = 0;
  currStudentTime = 0;
  currStudent = NULL;
  isEmpty = true;
}
bool Window::isWindowEmpty(){
  return isEmpty;
}
// Handles everything that the window needs to do at each tick
// Specifically, keeps track of time idle time and sends students home (making the window empty again)
void Window::processTick(int tick){
  //if curr student null, idle time
  if (isEmpty) {
    idleTime++;
  }
  else {
    // Increment service time and check if student`s time is up
    inServiceTime++;
    if (currStudentTime <= inServiceTime){
      //send student home
      isEmpty = true;
    }
  }
}
// Accept a new student to service at the window
void Window::acceptStudent(Student *student){
  currStudent = student;
  isEmpty = false;
  currStudentTime = student->serviceTime;
}
