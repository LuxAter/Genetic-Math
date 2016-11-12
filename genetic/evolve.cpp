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
  for (int i = 0; i < populationsize; i++) {
    if (population[i].value == goalvalue) {
      population[i].fitness = 1000;
    } else {
      population[i].fitness =
          std::fabs((double)1 / (double)(goalvalue - population[i].value));
    }
  }
}

void genetic::evolve::Killoff() {
  while (population.size() > ceil(populationsize / (double)2)) {
    population.erase(population.begin() + SelectLow());
  }
}

void genetic::evolve::Reproduce() {
  std::vector<Chromosome> newpop;
  std::vector<Chromosome> usedparents;
  bool doubleup = false;
  while (newpop.size() + usedparents.size() < populationsize) {
    display::DisplayAll(false, true, false, true);
    if (population.size() < 1) {
      population.insert(population.begin(), usedparents.begin(),
                        usedparents.end());
      doubleup = true;
      Sort();
    }
    Chromosome newchromosome;
    int parentone = SelectHigh();
    if (doubleup == false) {
      usedparents.push_back(population[parentone]);
    }
    population.erase(population.begin() + parentone);
    parentone = usedparents.size() - 1;
    if (population.size() < 1) {
      population.insert(population.begin(), usedparents.begin(),
                        usedparents.end());
      doubleup = true;
      Sort();
    }
    int parenttwo = SelectHigh();
    if (doubleup == false) {
      usedparents.push_back(population[parenttwo]);
    }
    population.erase(population.begin() + parenttwo);
    parenttwo = usedparents.size() - 1;
    for (int i = 0; i < chromosomelength * 4; i += 4) {
      if (drand() < 0.5) {
        for (int j = i; j < i + 4; j++) {
          newchromosome.bits += usedparents[parenttwo].bits[j];
        }
      } else {
        for (int j = i; j < i + 4; j++) {
          newchromosome.bits += usedparents[parentone].bits[j];
        }
      }
    }
    std::cout << "[ ";
    display::DrawEquation(usedparents[parentone], true);
    std::cout << " ] + [ ";
    display::DrawEquation(usedparents[parenttwo], true);
    std::cout << " ] = [ ";
    display::DrawEquation(newchromosome, true);
    std::cout << " ]\n";
    newpop.push_back(newchromosome);
  }
  population.clear();
  population = usedparents;
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
  bool selected = false;
  double cumulativefiteness = 0, cumulativefitenessbase = 0;
  if (population.size() == 1) {
    return (0);
  }
  for (int i = 0; i < population.size(); i++) {
    cumulativefitenessbase += population[i].fitness;
  }
  while (selected == false) {
    double cutoff = drand() * totalfitness;
    cumulativefiteness = cumulativefitenessbase;
    for (int i = 0; i < population.size(); i++) {
      if (cumulativefiteness > cutoff) {
        selected = true;
        return (i);
      } else {
        cumulativefiteness -= population[i].fitness;
      }
    }
  }
}

int genetic::evolve::SelectLow() {
  bool selected = false;
  double cumulativefiteness = 0;
  double cutoff = drand() * totalfitness;
  while (selected == false) {
    cumulativefiteness = 0;
    for (int i = population.size(); i > 0; i--) {
      if (cumulativefiteness < cutoff) {
        selected = true;
        return (i);
      } else {
        cumulativefiteness += population[i].fitness;
      }
    }
  }
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
