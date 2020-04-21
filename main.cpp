#include <iostream>
#include "Simulation.h"

int main (int argc, char **argv){
  //Run simulation
  Simulation *sim = new Simulation(argv[1]);
  sim->runSimulation();
}
