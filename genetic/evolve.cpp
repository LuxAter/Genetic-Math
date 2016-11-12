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
namespace evolve {
double totalfitness = 0;
bool doubleup = false;
}
}

void genetic::evolve::GenorateBasePopulation() {
  for (int i = 0; i < populationsize; i++) {
    Chromosome newchromosome;
    for (int j = 0; j < chromosomelength * 4; j++) {
      newchromosome.bits += std::to_string(rand() % 2);
    }
    population.push_back(newchromosome);
  }
}

void genetic::evolve::CalculateValues() {
  for (int i = 0; i < populationsize; i++) {
    std::string localbits = population[i].bits;
    bool loadoperator = false;
    int storedoperator = 0;
    double value = 0;
    for (int j = 0; j < localbits.size(); j += 4) {
      double bit = 0;
      for (int k = j; k < j + 4; k++) {
        if (localbits[k] == '1') {
          bit += pow(2, (3 - (k - j)));
        }
      }
      if (bit < 10 && loadoperator == false) {
        if (storedoperator == 10) {
          value += bit;
        } else if (storedoperator == 11) {
          value -= bit;
        } else if (storedoperator == 12) {
          value *= bit;
        } else if (storedoperator == 13) {
          value /= bit;
        } else if (storedoperator == 0) {
          value = bit;
          storedoperator = -1;
        }
        loadoperator = true;
      } else if (bit > 9 && bit < 14 && loadoperator == true) {
        storedoperator = bit;
        loadoperator = false;
      }
    }
    population[i].value = value;
  }
}

void genetic::evolve::CalculateFitness() {
  for (int i = 0; i < population.size(); i++) {
    if (population[i].value == goalvalue) {
      population[i].fitness = 1000;
    } else {
      population[i].fitness =
          std::fabs((double)1 / (double)(goalvalue - population[i].value));
    }
  }
}

void genetic::evolve::CumulateFitness() {
  double fitness = 0;
  for (int i = population.size() - 1; i >= 0; i--) {
    fitness += population[i].fitness;
    population[i].cumulativefitness = fitness;
  }
}

void genetic::evolve::Killoff() {
  std::vector<Chromosome> living;
  while (living.size() < ceil(populationsize / (double)2)) {
    int pointer = SelectHigh();
    living.push_back(population[pointer]);
    population.erase(population.begin() + pointer);
  }
  population.clear();
  population = living;
}

void genetic::evolve::Reproduce() {
  std::vector<Chromosome> newpop;
  std::vector<Chromosome> parents = population;
  doubleup = false;
  while (newpop.size() + parents.size() < populationsize) {
    Chromosome newchromosome;
    int parentone = SelectHigh();
    int parenttwo = parentone;
    while (parenttwo == parentone) {
      parenttwo = SelectHigh();
    }
    for (int i = 0; i < chromosomelength * 4; i += 4) {
      if (drand() < 0.5) {
        for (int j = i; j < i + 4; j++) {
          newchromosome.bits += population[parenttwo].bits[j];
        }
      } else {
        for (int j = i; j < i + 4; j++) {
          newchromosome.bits += population[parentone].bits[j];
        }
      }
    }
    newpop.push_back(newchromosome);
  }
  population.clear();
  population = parents;
  population.insert(population.end(), newpop.begin(), newpop.end());
}

void genetic::evolve::Mutate() {
  for (int i = 0; i < populationsize; i++) {
    for (int j = 0; j < chromosomelength * 4; j++) {
      if (drand() < mutationrate) {
        if (population[i].bits[j] == '1') {
          population[i].bits[j] = '0';
        } else if (population[i].bits[j] == '0') {
          population[i].bits[j] = '1';
        }
      }
    }
  }
}

int genetic::evolve::SelectHigh() {
  double point = drand() * totalfitness;
  for (int i = population.size(); i >= 0; i--) {
    // std::cout << point << ":" << population[i].cumulativefitness << "\n";
    if (population[i].cumulativefitness > point) {
      return (i);
    }
  }
  return (0);
}

int genetic::evolve::SelectLow() {
  double point = drand() * totalfitness;
  for (int i = 0; i < population.size(); i++) {
    std::cout << point << ":" << population[i].cumulativefitness << "\n";
    if (population[i].cumulativefitness < point) {
      return (i);
    }
  }
  return (0);
}

void genetic::evolve::SumFitness() {
  for (int i = 0; i < population.size(); i++) {
    totalfitness += population[i].fitness;
  }
}

void genetic::evolve::Sort() {
  std::sort(population.begin(), population.end(), SortCheck);
}

bool genetic::evolve::SortCheck(const Chromosome a, const Chromosome b) {
  return a.fitness > b.fitness;
}
