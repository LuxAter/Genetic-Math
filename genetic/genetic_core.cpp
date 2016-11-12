#include "../induco.h"
#include "display.h"
#include "evolve.h"
#include "genetic_core.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace genetic {
int populationsize = 100, chromosomelength = 10, genoration = 0;
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
  bool running = true;
  evolve::GenorateBasePopulation();
  // display::DisplayAll(false, true, true, false);
  display::DrawStats(true);
  genoration = 0;
  while (running == true) {
    if (genoration > 0) {
      running = false;
    }
    evolve::CalculateValues();
    evolve::CalculateFitness();
    evolve::SumFitness();
    evolve::Sort();
    evolve::CumulateFitness();
    display::DisplayAll(false, true, false, false, true);
    if (population[0].value == goalvalue) {
      running = false;
      break;
    } else {
      // display::DrawStats();
      evolve::Killoff();
      induco::Line(20);
      display::DisplayAll(false, true, false, false, true);
      evolve::Reproduce();
      // evolve::Mutate();
    }
    genoration++;
    induco::Line(10);
  }
  population.clear();
  return (0.0);
}

double genetic::drand() { return (fabs((double)rand() / (RAND_MAX + 1))); }
