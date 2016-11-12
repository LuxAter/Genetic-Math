#include "../induco.h"
#include "genetic_core.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace genetic {
int populationsize = 100, chromosomelength = 10;
double goalvalue = 1000, crossoverrate = 0.7, mutationrate = 0.001;
std::vector<Chromosome> population;
}

double genetic::RunAlgorithm(int popsize, int chrolength, double gova,
                             double crossrate, double mutrate) {
  if (popsize != 0) {
    populationsize = popsize;
  }
  if (chrolength != 0) {
    chromosomelength = chrolength;
  }
  goalvalue = gova;
  crossoverrate = crossrate;
  mutationrate = mutrate;
  return (0.0);
}

double drand() { return (fabs((double)rand() / (RAND_MAX + 1))); }
