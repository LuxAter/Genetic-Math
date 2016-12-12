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
double goalvalue = 1000, mutationrate = 0.001;
std::vector<Chromosome> population;
}

double genetic::RunAlgorithm(double gova, int popsize, int chrolength,
                             double mutate) {
  if (popsize != -1) {
    populationsize = popsize;
  }
  if (chrolength != -1) {
    chromosomelength = chrolength;
  }
  if (gova != -1) {
    goalvalue = gova;
  } else if (gova == -1) {
    goalvalue = rand() % 1000;
  }
  if (mutate != -1) {
    mutationrate = mutate;
  }
  bool running = true;
  evolve::GenorateBasePopulation();
  display::DrawStats(true);
  genoration = 0;
  while (running == true) {
    if (genoration == 1000) {
      running = false;
      break;
    }
    evolve::CalculateValues();
    evolve::CalculateFitness();
    evolve::SumFitness();
    evolve::Sort();
    evolve::CumulateFitness();
    if (population[0].value == goalvalue) {
      running = false;
      break;
    } else {
      display::DrawStats();
      evolve::Killoff();
      evolve::Reproduce();
      evolve::Mutate();
    }
    genoration++;
  }
  if (population[0].value == goalvalue) {
    induco::Break();
    std::cout << "Solved in " << genoration << "\n";
    display::DrawChromosome(0);
    display::DrawEquation(0);
  } else {
    induco::Break();
    std::cout << "Failed to solve in " << genoration << "\n";
    std::cout << "Closest value to [" << goalvalue << "]:\n";
    display::DrawChromosome(0);
    display::DrawEquation(0);
  }
  Clean();
  return (0.0);
}

double genetic::drand() { return (fabs((double)rand() / (RAND_MAX + 1))); }

void genetic::Clean() {

  population.clear();
  goalvalue = 0;
  populationsize = 0;
  chromosomelength = 0;
  genoration = 0;
  mutationrate = 0;
  evolve::totalfitness = 0;
  evolve::totalbottemup = 0;
}
